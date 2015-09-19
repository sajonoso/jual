/*
** Copyright 2015 Sajon Oso
** Native module interface
** See Copyright Notice in lua.h
*/


#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


#define OBJ_TYPE_ERROR "userdata type expected"

typedef struct usrObject {
    size_t size;                // Variable data size
    void *ptr;                  // Generic pointer
    unsigned char values[1];    // Variable data
} usrObject;


// LUA interface functions and objects
typedef struct jual_xapi_ {
    int STRBUFFER_SIZE;
    void *LS;
    void *fnGetNumber;
    void *fnGetString;
    void *fnGetObject;
    void *fnNumberPush;
    void *fnStrInit;
    void *fnStrAppend;
    void *fnStrPush;
} jual_xapi;

jual_xapi XAPI_TABLE;

int defGetNumber(void *LS, int argnum)
{
    lua_State *L = (lua_State *)LS;
    return luaL_checkinteger(L, argnum+1);
}

const char *defGetString(void *LS, int argnum, size_t *tSize)
{
    lua_State *L = (lua_State *)LS;
    const char *szResult = lua_tolstring(L, argnum+1, tSize);
    return szResult;
}

void *defGetObject(void *LS, int argnum)
{
    lua_State *L = (lua_State *)LS;
    return lua_touserdata(L, argnum+1);
}

void defNumberPush(void *LS, int iValue)
{
    lua_State *L = (lua_State *)LS;
    lua_pushinteger(L, iValue);
}

char *defStrInit(void *LS, void *strBuf, size_t tSize)
{
    lua_State *L = (lua_State *)LS;

    return luaL_buffinitsize(L, ((luaL_Buffer *)strBuf), tSize);
}

void defStrAppend(void *strBuf, const char *szValue, size_t tSize)
{
    luaL_addlstring( (luaL_Buffer *)strBuf, szValue, tSize);
}

void defStrPush(void *strBuf)
{
    luaL_pushresult( (luaL_Buffer *)strBuf );
}

typedef int ffifunc(void *funcList);


#if defined(LUA_USE_WINDOWS)
int GetExecutablePath(char *szPath, int iSize) {
    int iPathSize = GetModuleFileName(NULL, szPath, iSize);
    szPath[iSize-1] = '\0';
    if (iPathSize == 0) return -1;

   // remove executablename
    int i;
    for (i=iPathSize; i>1; i--) {
        if (szPath[i] != '\\') {
            szPath[i] = '\0';
        } else {
            szPath[i] = '\0';
            break;
        };
    };
    return 0;
}
#endif

#if defined(LUA_USE_LINUX)
int GetExecutablePath(char *szPath, int iSize) {
    char path[PATH_MAX];
    char dest[PATH_MAX];
    pid_t pid = getpid();
    sprintf(path, "/proc/%d/exe", pid);
    if (readlink(path, dest, PATH_MAX) == -1) return -1;
    int iPathSize = strlen(dest);
    if (iPathSize > iSize-1) return -2;
    strcpy(szPath, dest);

    // remove executablename
    int i;
    for (i=iPathSize; i>1; i--) {
        if (szPath[i] != '/') {
            szPath[i] = '\0';
        } else {
            szPath[i] = '\0';
            break;
        };
    };
    return 0;
};
#endif

// UNTESTED
#if defined(LUA_USE_MACOSX)
int GetExecutablePath(char *szPath, int iSize) {
    char pathbuf[PATH_MAX + 1];
    char *bundle_id;

    _NSGetExecutablePath( pathbuf, &bufsize);
	bundle_id = dirname(pathbuf);
    int iPathSize = strlen(bundle_id);
    if (iPathSize > iSize-1) return -2;
	strcpy(szPath, bundle_id);
    return 0;
};
#endif


void *LoadJualModule(lua_State *L, const char *szModuleName) {

#if (PATH_MAX < 64)
   #error "PATH_MAX is too low on this system"
#endif

    char szBuffer[PATH_MAX]; // PATH_MAX defined in unistd.h and equals 260 in windows
    strcpy(szBuffer, szModuleName);

// non windows systems need extension
#if !defined(LUA_USE_WINDOWS)
    strcat(szBuffer, ".so");    
#endif

    void *reg = checkclib(L, szModuleName);
    if (reg == NULL) {  // must load library?
        reg = lsys_load(L, szBuffer, 0xFF);  // 0xFF == global

// try executable, then current path on non-windows systems if module not found in standard paths
#if !defined(LUA_USE_WINDOWS)
        if (reg == NULL) {
            if (GetExecutablePath(szBuffer, PATH_MAX) != 0) {
                return NULL;
            };
            strcat(szBuffer, "/");
            strcat(szBuffer, szModuleName);
            strcat(szBuffer, ".so");
            reg = lsys_load(L, szBuffer, 0xFF);  
        };
        
        if (reg == NULL) {
            strcpy(szBuffer, "./");
            strcat(szBuffer, szModuleName);
            strcat(szBuffer, ".so");
            reg = lsys_load(L, szBuffer, 0xFF);  
        };        
#endif

        if (reg == NULL) {
            return NULL;
        };
        addtoclib(L, szModuleName, reg);        
    };

    return reg;
}

void ffi_setexecutablepath(lua_State *L) {
    char szBuffer[PATH_MAX];
    if (GetExecutablePath(szBuffer, PATH_MAX) != 0) return;
    int iPathSize=strlen(szBuffer);

    lua_pushlstring(L, szBuffer, iPathSize);
    lua_setfield(L, -2, "ffi_ExecutablePath");
}


LUALIB_API int ffi_require(lua_State *L) {
    size_t iLen;
    const char *szModuleName = lua_tolstring(L, 1, &iLen);

    if ( (szModuleName == NULL) || (iLen > 32)) {
        // lua_pushnil(L);
        lua_pushinteger(L, -1);
        return 1;
    };

    void *reg = LoadJualModule(L, szModuleName);
    if (reg == NULL) {
        return luaL_error(L, "ERROR: module '%s' could not be loaded", szModuleName);
        // lua_pushinteger(L, -2);
        // return 1;        
    };

    char szBuffer[PATH_MAX];
    strcpy(szBuffer, szModuleName);
    if (strlen(szBuffer) < 120) strcat(szBuffer, "_init");

    lua_CFunction cf = lsys_sym(L, reg, szBuffer);
    if (cf == NULL) {
        lua_pushinteger(L, -3);
        return 1;
    };

    lua_pushstring(L, szModuleName);
    int iRet = ((ffifunc *)cf)(&XAPI_TABLE);

    const char *szResult = lua_tolstring(L, -1, NULL);

    iRet = luaL_dostring(L, szResult);
    if (iRet) { // error in initialization script
        return luaL_error(L, "ERROR in module '%s' initialization script", szModuleName);
    };

    return 0;
}


/*
    Creates a new userdata block
*/
LUALIB_API int ffi_newuserdata (lua_State *L) {
    size_t nbytes;
    size_t sLen;
    usrObject *a;

    if (lua_isinteger(L, 1)) {
        int iLen = luaL_checkinteger(L, 1);
        // printf("new array %d\r\n", iLen);
        sLen = iLen;
        nbytes = sizeof(usrObject) + iLen;
        a = (usrObject *)lua_newuserdata(L, nbytes);
    } else {
        const char *szText = lua_tolstring(L, 1, &sLen);
        // printf("new array string %d\r\n", sLen);
        nbytes = sizeof(usrObject) + sLen*sizeof(char);
        a = (usrObject *)lua_newuserdata(L, nbytes);
        strcpy(a->values, szText); // copy string including null character
    };
    a->size = sLen;
    return 1;
}


LUALIB_API int ffi_userdatatable (lua_State *L) {
    size_t sLen;

    const char *szClassname = lua_tolstring(L, 2, &sLen);

    luaL_newmetatable(L, szClassname);  // new table or return existing table with classname
    lua_setmetatable(L, 1);             // set metatable for first parameter to new table.

    return lua_getmetatable(L,1);
}


LUALIB_API int ffi_ud2string (lua_State *L) {
    usrObject *ba = (usrObject *)lua_touserdata(L, 1);
    luaL_argcheck(L, ba != NULL, 1, OBJ_TYPE_ERROR);
    lua_pushlstring(L, ba->values, ba->size);
    return 1;
}


/*
  This function maps a module function to a LUA C Function.  Do not call these functions directly from LUA
  parm1 = module name
  parm2 = function name
*/
LUALIB_API int ffi_mapfunc(lua_State *L) {
    // size_t iLen;
    const char *szModuleName = lua_tolstring(L, 1, NULL);
    const char *szFunctionName = lua_tolstring(L, 2, NULL);
    
    if ( (szModuleName == NULL) || (szFunctionName == NULL)) {
        lua_pushnil(L);
        return 1;
    };

    void *reg = LoadJualModule(L, szModuleName);
    if (reg == NULL) {
        lua_pushnil(L);
        return 1;        
    };

    lua_CFunction f = lsys_sym(L, reg, szFunctionName);
    if (f == NULL) {
        lua_pushnil(L);
        return 1;
    };
    
    lua_pushcfunction(L, f);
    return 1;
}


/*
  Call a mapped function that returns a string
  parm1 = special C Function defined in typedef ffifunc
  parm2 = string input
*/
LUALIB_API int ffi_call(lua_State *L) {
    lua_CFunction cf = lua_tocfunction(L, 1);

    int iRet = ((ffifunc *)cf)(&XAPI_TABLE);
    return iRet;
}


static struct luaL_Reg ffi_funcs[] = {
    {"ffi_newobject", ffi_newuserdata},
    {"ffi_objecttable", ffi_userdatatable},
    {"ffi_tostring", ffi_ud2string},
    {"ffi_map", ffi_mapfunc},
    {"ffi_call", ffi_call},
    {"require_n", ffi_require},
    /* placeholders */
     {"ffi_ExecutablePath", NULL},    
    {NULL, NULL}
};


LUAMOD_API int luaopen_jualffi (lua_State *L) {
    lua_pushglobaltable(L);
    luaL_setfuncs(L, ffi_funcs, 0);

    ffi_setexecutablepath(L);

    XAPI_TABLE.STRBUFFER_SIZE = sizeof(luaL_Buffer) + 1;;
    XAPI_TABLE.LS = L;
    XAPI_TABLE.fnGetNumber = defGetNumber;
    XAPI_TABLE.fnGetString = defGetString;
    XAPI_TABLE.fnGetObject = defGetObject;
    XAPI_TABLE.fnNumberPush = defNumberPush;
    
    XAPI_TABLE.fnStrInit = defStrInit;
    XAPI_TABLE.fnStrAppend = defStrAppend;
    XAPI_TABLE.fnStrPush = defStrPush;

    return 1;
}
