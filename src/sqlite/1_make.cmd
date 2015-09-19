@echo off

gcc -Os -DSQLITE_OMIT_DEPRECATED=1 -DSQLITE_OMIT_LOAD_EXTENSION=1 -DSQLITE_THREADSAFE=0 -c sqlite3.c
ar rcs -o libsqlite_3.a sqlite3.o
gcc -shared -static -Os -o ../../bin/libsqlite3.dll libsqlite3.c -L. -lsqlite_3
del libsqlite_3.a sqlite3.o
