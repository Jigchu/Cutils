#!/usr/bin/bash

mingw32-make -f makefile.mk "$1"
mingw32-make -f makefile.mk clean

if [ -e bin/test.exe ] ; then
	rm -f bin/test.exe
fi