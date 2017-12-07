GTEST_DIR = .
TEST_DIR = src

# Flags passed to the preprocessor.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# All tests produced by this Makefile.
TESTS = demo11

# House-keeping build targets.
all : bin/$(TESTS)_unittest

clean :
	rm -f $(TESTS)_unittest obj/*.o bin/*

obj/$(TESTS).o : $(TEST_DIR)/$(TESTS).cc $(TEST_DIR)/$(TESTS).h 
	$(CXX) $(CPPFLAGS) -c $(TEST_DIR)/$(TESTS).cc -o obj/$(TESTS).o

obj/$(TESTS)_unittest.o : $(TEST_DIR)/$(TESTS)_unittest.cc $(TEST_DIR)/$(TESTS).h 
	$(CXX) $(CPPFLAGS) -c $(TEST_DIR)/$(TESTS)_unittest.cc -o obj/$(TESTS)_unittest.o

bin/$(TESTS)_unittest : obj/$(TESTS).o obj/$(TESTS)_unittest.o lib/gtest_main.a lib/gmock.a
	$(CXX) $(CPPFLAGS) $^ -o $@
	$@
