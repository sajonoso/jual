// exported functions

// ## INPUT
// LUA_API const char *lua_tolstring (lua_State *L, int idx, size_t *len)
// LUA_API lua_Integer lua_tointegerx (lua_State *L, int idx, int *pisnum)

// ## OUTPUT
// LUA_API const char *lua_pushlstring (lua_State *L, const char *s, size_t len)
// LUA_API void lua_pushinteger (lua_State *L, lua_Integer n)
// #define lua_pushliteral(L, s)	\
//	lua_pushlstring(L, "" s, (sizeof(s)/sizeof(char))-1)

#include <stdlib.h>

#define LUA_BUILD_AS_DLL
#define lvm_c

#include "..\lcode.c"
#include "..\lctype.c"
#include "..\ldebug.c"
#include "..\ldo.c"
#include "..\lfunc.c"
#include "..\lgc.c"
#include "..\lmem.c"
#include "..\lobject.c"
#include "..\lopcodes.c"
#include "..\lstate.c"
#include "..\lstring.c"
#include "..\ltable.c"
#include "..\ltm.c"
#include "..\lvm.c"
#include "..\lzio.c"

// #include "..\llex.c"
l_noret luaX_syntaxerror (LexState *ls, const char *msg) {
    luaD_throw(ls->L, LUA_ERRSYNTAX);
};

void luaX_init (lua_State *L) {
    return;
};


// #include "..\lparser.c"
LClosure *luaY_parser (lua_State *L, ZIO *z, Mbuffer *buff,
                       Dyndata *dyd, const char *name, int firstchar) {
  LClosure *cl;
  return cl;    
};


// #include "..\ldump.c"
int luaU_dump(lua_State *L, const Proto *f, lua_Writer w, void *data,
              int strip) {
    return 0;
};

// #include "..\lundump.c"
LClosure *luaU_undump(lua_State *L, ZIO *Z, Mbuffer *buff,
                      const char *name) {
  LClosure *cl;
  return cl;
};

#include "jauxlib.h"
#include "japi.h"
