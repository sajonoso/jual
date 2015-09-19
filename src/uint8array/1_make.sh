# No make required just gcc and standard C library
# .
gcc -Os -ldl -lm -DLUA_USE_LINUX -shared -o ../../bin/uint8array.so uint8array.c
