#include <stdio.h>
#include "jualmod.h"

// see file test_samplemod.js on how to use this module

LUALIB_API int myfunc(lua_State* L)
{
    size_t s1size;
    const char *s = lua_tolstring(L, 1, &s1size);
    if (s==NULL) { return 0; };

    luaL_Buffer bResult;

    char *z = luaL_buffinitsize(L, &bResult, s1size+1);
    int i;
    for (i = 0; i < s1size; i++) {
        z[i] = s[s1size-i-1];
    };
    z[s1size] = '\0';

    luaL_pushresultsize(&bResult, s1size);
    return 1;
}

static struct luaL_Reg funcs[] = {
  {"myfunc", myfunc},
  /* placeholders */
  {"mynum", NULL},
  {"myword", NULL},
  {NULL, NULL}
};

#define G_WORD "supercalifragilisticexpialidocious"
#define G_INT 31415927

LUAMOD_API int luaopen_samplemod (lua_State *L) {

// The below two lines import the functions into the global namespace
  /* open lib into global table */
  /* open lib into global table */
  lua_pushglobaltable(L);
  luaL_setfuncs(L, funcs, 0);

// The line below will import the functions into another namespace
// comment out the two lines above if enabling the line  below
//  luaL_newlib(L, funcs);

  lua_pushliteral(L, G_WORD);
  lua_setfield(L, -2, "myword");
  lua_pushinteger(L, (lua_Integer)G_INT);
  lua_setfield(L, -2, "mynum");
  return 1;
}

