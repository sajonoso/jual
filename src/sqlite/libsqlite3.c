/*
** Jual SQLite3 interface
*/

#include "jualmod.h"

#define SQLITE_OMIT_DEPRECATED 1
#define SQLITE_OMIT_LOAD_EXTENSION 1
#include "my_sqlite3.c"


const char *szFIELDSEP = "\t";
const char *szRECSEP = "\n";

LUALIB_API int sql3_execute(lua_State * L)
{
	int iResult = -1;
    size_t szLen;
	const char *sqldbname = lua_tolstring(L, 1, &szLen);
	const char *sqlstatement = lua_tolstring(L, 2, &szLen);
	sqlite3 *sql3db;

	if ( sqlite3_open( sqldbname, &sql3db ) == SQLITE_OK ) {
		if (sqlite3_exec( sql3db, sqlstatement, 0, 0, 0 ) == SQLITE_OK )
            iResult = sqlite3_changes(sql3db);
	};
	sqlite3_close( sql3db );

	lua_pushinteger(L, (lua_Integer)iResult);
	return 1;
}


LUALIB_API int sql3_query(lua_State * L)
{
	int retval;
    size_t szLen;
	const char *sqldbname = lua_tolstring(L, 1, &szLen);
	const char *sqlstatement = lua_tolstring(L, 2, &szLen);
    int iP3IsNumber; // is the third parameter a number
    int iUseRecordsep = lua_tointegerx(L, 3, &iP3IsNumber);
    if (!iP3IsNumber) { iUseRecordsep = 1; }; // default to use record separator

	sqlite3 *sql3db;
	sqlite3_stmt *stmt;
    int iLenFIELDSEP = strlen(szFIELDSEP);
    int iLenRECSEP = strlen(szRECSEP);
    luaL_Buffer bResult;
    char *sb = luaL_buffinitsize(L, &bResult, 64);

	if ( sqlite3_open( sqldbname, &sql3db ) == SQLITE_OK )
	{
		if ( sqlite3_prepare( sql3db, sqlstatement, -1,&stmt,0 ) == SQLITE_OK )
		{
			int iNumColumns = sqlite3_column_count(stmt);

			retval = sqlite3_step(stmt);
			while (retval == SQLITE_ROW)
			{
				int col;
				for ( col=0; col<iNumColumns; col++)
				{
					const char *val = (const char*)sqlite3_column_text(stmt,col);
					if (col > 0) luaL_addlstring(&bResult, szFIELDSEP, iLenFIELDSEP);
					if (val) luaL_addlstring(&bResult, val, strlen(val));
				};

                if (iUseRecordsep) {
                    luaL_addlstring(&bResult, szRECSEP, iLenRECSEP);
                    retval = sqlite3_step(stmt);
                } else {
                    retval = !SQLITE_ROW;
                };
			};
		};
	};

	sqlite3_close( sql3db );

	luaL_pushresult(&bResult);
	return 1;
}

static const luaL_Reg libsqlite3[] = {
	{"query", sql3_query},
	{"execute", sql3_execute},
	{NULL, NULL}
};

LUAMOD_API int luaopen_libsqlite3 (lua_State *L) {
  luaL_newlib(L, libsqlite3);
  return 1;
}
