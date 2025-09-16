# file: makefile
# description: This file is used to compile the program
# usage: 
#	make all - compile C programs respectively
#	make clean - remove the executable files

CC=gcc # choose compiler
CFLAGS=-I. -O0# choose compiler options. I. means include the current directory

# some symbols used in the makefile, meaning:
# $< means the first name after ":", i.e. the first dependency
# $@ means the name before ":"
# $^ means all the names after ":"
# % means any name

# this is a pattern rule 
# <target>:<prerequisites>
# <tab><command>
# it will compile C files to the executable file with the same name, respectively
%: %.c # % means any name ending with .c, as the prerequisites for the target(%, same name without .c)
	$(CC) -o $@ $< $(CFLAGS) 

# patsubst means pattern substitution, usage: patsubst(pattern, target, file)
# wildcard means find all the files matching the pattern, usage: wildcard(pattern)

# "all", a target, depends on all the executable files
all: $(patsubst %.c,%,$(wildcard *.c))

# "clean", a target, depends on nothing
clean:
	rm $(patsubst %.c,%,$(wildcard *.c))
