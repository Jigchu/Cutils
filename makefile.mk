# Some copy-paste from SO
ifeq ($(OS),Windows_NT)
	SHELL := bash.exe
else
	SHELL := /usr/bin/env bash
endif
.SHELLFLAGS := -eo pipefail -c

CC = gcc
CFLAGS = -O3 -Wall -fdiagnostics-color=always -I ${SDIR} -g

SDIR = utils/
TDIR = tests/
BDIR = bin/

test : test.exe
	./${BDIR}test

test-all : test.exe
	./${BDIR}test --all

test.exe : test.o deque_t.o colours_t.o colours.o
	${CC} ${CFLAGS} ${BDIR}test.o ${BDIR}deque_t.o ${BDIR}colours_t.o ${BDIR}colours.o -o ${BDIR}$@

test.o : ${TDIR}test.c
	${CC} ${CFLAGS} -c ${TDIR}test.c -o bin/$@

deque_t.o : ${TDIR}deque/deque_t.c ${TDIR}deque/deque_t.h
	${CC} ${CFLAGS} -c ${TDIR}deque/deque_t.c -o ${BDIR}$@

colours_t.o : ${TDIR}colours/colours_t.c ${TDIR}colours/colours_t.h
	${CC} ${CFLAGS} -c ${TDIR}colours/colours_t.c -o ${BDIR}$@

deque.o : ${SDIR}/deque/deque.c ${SDIR}/deque/deque.h
	${CC} ${CFLAGS} -c ${SDIR}/deque/deque.c -o ${BDIR}$@

colours.o : ${SDIR}/colours/colours.c ${SDIR}/colours/colours.h
	${CC} ${CFLAGS} -c ${SDIR}/colours/colours.c -o ${BDIR}$@

clean : 
	rm -f ${BDIR}*.o

full-clean :
	rm -r ${BDIR}*