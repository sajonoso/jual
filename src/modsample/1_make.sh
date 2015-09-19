# No make required just gcc and standard C library
# .
gcc -Os -shared -static -DLUA_USE_LINUX -o ../../bin/modsample.so modsample.c
