#=============================================================================
#     FileName: Makefile
#         Desc: Makefile for unit test
#       Author: LinFan
#        Email: linfan.china@gmail.com
#      Version: 1.0.0
#=============================================================================

# Using Google C++ Testing Framework (https://code.google.com/p/googletest/)

### DEFINITIONS

OUTFILE   = test_main
OUTDIR    = ../bin
TEST_OBJS = ../src/obj/InputReader.o \
			../src/obj/OutputCalculator.o \
			../src/obj/GalaxyTranslater.o \
			../src/obj/RomanTranslater.o
SRC       = $(wildcard *.cc)
OBJS      = $(SRC:%.cc=%.o)
OBJDIR    = obj
OBJFILES  = $(OBJS:%=$(OBJDIR)/%) $(TEST_OBJS)
CFLAGS    = -Wno-comment
CXX       = g++

### MAIN PROGRAMS

all: prepare $(OUTFILE)
	$(OUTDIR)/$(OUTFILE)

prepare:
ifneq ($(OBJDIR), $(wildcard $(OBJDIR)))
	mkdir -p "$(OBJDIR)"
endif
ifneq ($(OUTDIR), $(wildcard $(OUTDIR)))
	mkdir -p "$(OUTDIR)"
endif

$(OUTFILE): $(OBJFILES)
	$(CXX) -o $(OUTDIR)/$(OUTFILE) $^ lib/libgtest.a

$(OBJDIR)/%.o: %.cc
	$(CXX) -c -isystem include -I../src $*.cc -o $(OBJDIR)/$*.o -fPIC -std=c++11 -g $(CFLAGS)

clean:
	rm -fr $(OUTFILE) $(OBJDIR)

