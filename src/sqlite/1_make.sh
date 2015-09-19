# No make required just gcc and standard C library
# .
gcc -Os -DSQLITE_OMIT_DEPRECATED=1 -DSQLITE_OMIT_LOAD_EXTENSION=1 -DSQLITE_THREADSAFE=0 -c sqlite3.c
ar rcs libsqlite_3.a sqlite3.o
gcc -Os -ldl -lm -DLUA_USE_LINUX -shared -o ../../bin/libsqlite3.so libsqlite3.c -L. -lsqlite_3
# rm libsqlite_3.a sqlite3.o
