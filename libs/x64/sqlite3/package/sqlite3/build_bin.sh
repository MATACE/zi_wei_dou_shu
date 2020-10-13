#!/bin/bash

cd src

CC=gcc
AR=ar
AR_FLAG=-rcv
THREAD_SAFE=-DSQLITE_THREADSAFE=2
# If not need extern load sqlite3_load_extension() and load_extension() function feature.
NO_EXTERN=-DSQLITE_OMIT_LOAD_EXTENSION

# Build the sqlit3 bin.
$CC $THREAD_SAFE shell.c sqlite3.c -lpthread -ldl -o sqlite3

# Builde the sqlite3 dynamic lib.
$CC $THREAD_SAFE -o sqlite3.o sqlite3.c -c -fPIC -lpthread -ldl
$CC $THREAD_SAFE -o libsqlite3.so sqlite3.o -shared
rm -rf sqlite3.o

# Builde the sqlite3 static lib.
$CC $THREAD_SAFE -o sqlite3.o -c sqlite3.c -fPIC -lpthread -ldl
$AR $AR_FLAG libsqlite3.a sqlite3.o
rm -rf sqlite3.o

rm -rf ../lib/include/* ../lib/lib/*
cp sqlite3.h ../lib/include/
mv libsqlite3.a libsqlite3.so sqlite3 ../lib/lib/

