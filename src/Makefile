#!/usr/bin/make -f

SHELL = /bin/sh

topdir = ..
srcdir = $(topdir)/src

CC = clang
INSTALL = /usr/local/bin/install -c
INSTALLDATA = /usr/local/bin/install -c -m 644

LANG = c
STD = c17
CDEBUG = -g -DDEBUG
CFLAGS = $(CDEBUG) -Wall -pedantic -O2
DEFS = 
CPPFLAGS = -I. -I$(srcdir) $(DEFS)
LDFLAGS = 

LIBS = -lncurses

prefix = /usr/local
binprefix =

bindir = $(prefix)/bin

SRCS_C = main.c orbdef.c \
	 dice.c \
	 entity.c stbl.c \
	 tower.c shell.c wall.c \
	 soldier.c
SRCS = $(SRCS_C)
OBJS = $(SRCS_C:.c=.o)

AUX = README COPYING

.ONESHELL:

.EXPORT_ALL_VARIABLES:

.SUFFIXES:
.SUFFIXES: .c .o .h

.c.o:
	$(CC) -c -xc -std=c17 $(CPPFLAGS) $(CFLAGS) $< -o $@

.PHONY: all
all: orbdef

.PHONY: install
install: all
	$(INSTALL) orbdef $(bindir)/$(binprefix)orbdef

.PHONY: TAGS tags
TAGS: $(SRCS)
	ctags $^

tags: TAGS

.PHONY: clean realclean distclean
clean:
	rm -f *.o

realclean: clean
	rm -f orbdef TAGS tags

distclean: realclean

orbdef: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LIBS) -o $@

main.o: orbdef.o

orbdef.o: tower.o

tower.o: shell.o

shell.o: wall.o

entity.o: stbl.o

stbl.o: dice.o

soldier.o: entity.o stbl.o clrpr.h
