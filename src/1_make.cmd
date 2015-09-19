rem Simple compile script
cls
gcc -DWINVER=0x0501 -Os -static -o ../bin/jualc.exe ./2_jualc.c
gcc -DWINVER=0x0501 -Os -static -o ../bin/jual.exe ./3_jual.c
