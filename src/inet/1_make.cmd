@cls
@gcc -Wall -DLUA_USE_WINDOWS -DWINVER=0x0501 -Os -shared -static -o ../../bin/libinet.dll inet.c -lws2_32 -lMswsock -lAdvApi32
