#include <stdio.h>
#include "jualmod.h"

/*

This sample module has one function that simply accepts a string as input and returns a string as output.

Test this module with the following code:

sztst="This sentence will be reversed";
myfunc = package.loadlib("samplemod2.dll", "foobar");
szResult = myfunc(sztst);
print(szResult);

*/


LUALIB_API int foobar(lua_State* L)
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
    // lua_pushinteger(L, (lua_Integer)1234);
    // lua_pushliteral(L, "hello");
    return 1;
}
