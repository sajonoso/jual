# No make required just gcc and standard C library
# .
gcc -Os -ldl -lm -DLUA_USE_LINUX -o ../bin/jualc ./2_jualc.c
gcc -Os -ldl -lm -DLUA_USE_LINUX -o ../bin/jual ./3_jual.c
