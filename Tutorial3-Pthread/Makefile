# Use makefile to compile your C code.
# Usage: 
# make all - compile all c files in the same dir
# make clean - clean all the compiled files


# define variables
CFLAGS=-Wall -pthread
CC=gcc

# patsubst (subst from,to,text)
# Performs a textual replacement on the text text: each occurrence of 
# from is replaced by to.

SRCS =$(wildcard *.c)
OBJS =$(patsubst %.c,%,$(SRCS))

# <target>:<dependencies>
all:$(OBJS)

# $< first item on the right side of ":"
# $@ left side of ":""
# % any 

%:%.c
	$(CC) $(CFLAGS) -o $@ $<

# tell make program not to treat "clean" and "all" as a filename
.PHONY: clean all

clean:
	rm -f $(OBJS)
