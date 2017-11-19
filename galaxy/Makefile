#=============================================================================
#     FileName: Makefile
#         Desc: Top level makefile
#       Author: LinFan
#        Email: linfan.china@gmail.com
#      Version: 1.0.0
#=============================================================================

# Build main project and unit test
.PHONY: all build unittest clean distclean tags

# Default task
all: build unittest
	echo "Done."

# Build source code
build:
	$(MAKE) all -C src

# Bulid and run unittest
unittest:
	$(MAKE) all -C unittest

# Create document file
doxygen:
	$(MAKE) doxygen -C src

# Clean object and output files
clean:
	$(MAKE) clean -C src
	$(MAKE) clean -C unittest
	rm -fr bin

# Clean all generated files
distclean: clean
	find . -name core.* -exec rm -rf {} \;
	rm -f src/tags src/cscope.* 

# Create ctags file
tags:
	$(MAKE) tags -C src

