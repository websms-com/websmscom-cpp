
include ../project.mk

GMOCK_DIR = gmock/
GMOCK_BIN = $(GMOCK_DIR)/make
GMOCK_INCLUDE = -I$(GMOCK_DIR)/include

GTEST_DIR = $(GMOCK_DIR)/gtest
GTEST_BIN = $(GTEST_DIR)/make
GTEST_INCLUDE = -I$(GTEST_DIR)/include

LIB_DIR := ../src/
LIB_SOURCES := $(wildcard $(LIB_DIR)/*.cc)
LIB_OBJS := $(patsubst $(LIB_DIR)/%.cc, %.o, $(LIB_SOURCES))

TEST_SOURCES := $(wildcard *.cc)
TEST_OBJS := $(patsubst %.cc, %.o, $(TEST_SOURCES))

PROGRAM := run_tests
INCLUDE := -I../include -I../src $(GTEST_INCLUDE) $(GMOCK_INCLUDE)
LIBS := -lcurl -ljansson -lpthread
CXX := g++
CXXFLAGS := -g -Wall -Wextra \
	-fprofile-arcs -ftest-coverage

$(PROGRAM): $(LIB_OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(LIB_OBJS) $(TEST_OBJS) \
	$(GMOCK_BIN)/gmock.a $(LIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

%.o: $(LIB_DIR)/%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

coverage: $(PROGRAM)
	./$(PROGRAM)
	gcov -r $(LIB_OBJS)

memcheck: $(PROGRAM)
	valgrind --leak-check=full ./$(PROGRAM)

clean:
	rm -f *.o *.gcno *.gcda *.gcov $(PROGRAM)

.PHONY: clean coverage memcheck
