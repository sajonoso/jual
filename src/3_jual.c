/*
* one.c -- Lua core, libraries, and interpreter in a single file
run "gcc -E" to generate preprocessor output only
*/

/* default is to build the full interpreter */
#ifndef MAKE_LIB
#ifndef MAKE_LUAC
#ifndef MAKE_LUA
#define MAKE_LUA
#endif
#endif
#endif

/* choose suitable platform-specific features */
/* some of these may need extra libraries such as -ldl -lreadline -lncurses */
#if 0
// #define LUA_USE_LINUX
// #define LUA_USE_MACOSX
// #define LUA_USE_POSIX
#define LUA_ANSI
#endif

// The byte array and sqlite3 modules can be integrated into the VM interpreter by uncommenting the line below
// #define BUILTIN_MODULES

#define luaall_c
#define lobject_c

/* core -- used by all */
#include "lapi.c"
#include "lcode.c"
#include "lctype.c"
#include "ldebug.c"
#include "ldo.c"
#include "ldump.c"
#include "lfunc.c"
#include "lgc.c"
#include "llex.c"
#include "lmem.c"
#include "lobject.c"
#include "lopcodes.c"
#include "lparser.c"
#include "lstate.c"
#include "lstring.c"
#include "ltable.c"
#include "ltm.c"
#include "lundump.c"
#define pushclosure pushclosure2
#include "lvm.c"
#include "lzio.c"

/* auxiliary library -- used by all */
#include "lauxlib.c"

/* standard library  -- not used by luac */
#ifndef MAKE_LUAC
#include "lbaselib.c"
// LUA_COMPAT_BITLIB
// #include "lbitlib.c"
#include "lcorolib.c"
#include "ldblib.c"
#include "liolib.c"
#define LUA_COMPAT_MATHLIB
#include "lmathlib.c"
#include "loadlib.c"
#include "loslib.c"
#include "lstrlib.c"
#include "ltablib.c"
#include "lutf8lib.c"
// #include "loadlib.c"
#include "linit.c"
#endif

/* lua */
#ifdef MAKE_LUA
// don't use readline library
#undef LUA_USE_READLINE
#include "lua.c"
#endif

/* luac */
#ifdef MAKE_LUAC
// #include "print.c"
#include "luac.c"
#endif