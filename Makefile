#!/usr/bin/make -f

SHELL = /bin/sh

topdir = .
srcdir = $(topdir)/src


.PHONY: all
all:
	$(MAKE) -C $(srcdir) all

.PHONY: orbdef
wizbat:
	$(MAKE) -C $(srcdir) wizbat

.PHONY: install
	$(MAKE) -C $(srcdir) install

.PHONY: TAGS tags
TAGS:
	$(MAKE) -C $(srcdir) TAGS

tags: TAGS

.PHONY: clean realclean distclean
clean:
	rm -rf *.dSYM
	$(MAKE) -C $(srcdir) clean

realclean: clean
	$(MAKE) -C $(srcdir) realclean

distclean: realclean
	$(MAKE) -C $(srcdir) distclean
