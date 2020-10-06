CC = clang
CCFLAGS = -std=c89 -Wall -pedantic


switch:
	python3 build-switch-statement.py > switch.c

all: main.c sm83.h sm83.c sm83_opcodes.h sm83_opcodes.c
	$(CC) $(CCFLAGS) main.c sm83.c sm83_opcodes.c -o libtest

run: all
	./libtest

watch:
	find $(wildcard *.[ch]) | entr -c -r make run

