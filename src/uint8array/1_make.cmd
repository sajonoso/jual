@cls
@gcc -Wall -DLUA_USE_WINDOWS -DWINVER=0x0501 -Os -shared -static -o ../../bin/uint8array.dll uint8array.c