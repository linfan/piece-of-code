#=============================================================================
#     FileName: Makefile
#         Desc: Makefile for source codes
#       Author: LinFan
#        Email: linfan.china@gmail.com
#      Version: 1.0.0
#=============================================================================

### DEFINITIONS

OUTFILE   = main
OUTDIR    = ../bin
SRC       = $(wildcard *.cc)
OBJS      = $(SRC:%.cc=%.o)
OBJDIR    = obj
OBJFILES  = $(OBJS:%=$(OBJDIR)/%)
DOCDIR    = ../doc
CFLAGS    = -Wno-comment
CXX       = clang++

### MAIN PROGRAMS

all: prepare $(OUTFILE)

prepare:
ifneq ($(OBJDIR), $(wildcard $(OBJDIR)))
	mkdir -p "$(OBJDIR)"
endif
ifneq ($(OUTDIR), $(wildcard $(OUTDIR)))
	mkdir -p "$(OUTDIR)"
endif

$(OUTFILE): $(OBJFILES)
	$(CXX) $^ -o $(OUTDIR)/$(OUTFILE) $(LFLAGS)
	#strip $(OUTDIR)/$(OUTFILE)

$(OBJDIR)/%.o: %.cc
	$(CXX) -c $*.cc -o $(OBJDIR)/$*.o $(CFLAGS) -fPIC -std=c++11 -g

doxygen:
ifneq ($(DOCDIR), $(wildcard $(DOCDIR)))
	mkdir -p "$(DOCDIR)"
endif
	doxygen ./Doxyfile

clean:
	rm -fr $(OUTFILE) $(OBJDIR) $(DOCDIR)
	
tags:
	ctags --languages=c++ --fields=+SKz --sort=foldcase *.cc

