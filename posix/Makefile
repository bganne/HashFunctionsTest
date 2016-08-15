CFLAGS:=-g -Wall -Werror -Wno-sign-compare
CFLAGS+= -O2
CFLAGS+= -msse4
CXXFLAGS:=$(CFLAGS)
LDFLAGS:=-g
LDLIBS:=-lm

TOPDIR:=..
HASHDIR:=$(TOPDIR)/HashFunctions
SOURCES_EXT:=.c .cc .cpp

obj-files=$(patsubst %$(ext), %.o, $(wildcard $(HASHDIR)/*$(ext)))
obj:=$(foreach ext, $(SOURCES_EXT), $(obj-files))

all: $(TOPDIR)/main

$(TOPDIR)/main: $(TOPDIR)/main.cpp $(obj)

clean:
	$(RM) $(TOPDIR)/main $(TOPDIR)/main.o $(obj)

.PHONY: all clean
