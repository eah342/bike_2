# Makefile for Self-balancing bike test interface
# test

EXEC_NAME := "test"
INCLUDE_DIR := "/home/debian/servoLibs/inc/inc-pub"
LIBS := -lsFoundation20 -lpthread
CC := g++
OPTIMIZATION := -O3
DEBUG_OPTIMIZATION := -O0
CXXFLAGS := -I$(INCLUDE_DIR) $(OPTIMIZATION)
DEBUG_CXXFLAGS := $(CXXFLAGS) -Wall -Wextra -pedantic -g3 $(DEBUG_OPTIMIZATION)
RPATH := "/home/debian/teknic"

# Specify source files here
ALL_SRC_FILES := $(wildcard *.cpp)
ALL_OBJS := $(patsubst %.cpp,%.o,$(ALL_SRC_FILES))

# Default target
all: test

# Generic rule to compile a CPP file into an object
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o "$@" $<

test: $(ALL_OBJS)
	$(CC) -L$(RPATH) -Wl,-rpath=$(RPATH) -o $(EXEC_NAME) $(ALL_OBJS) $(LIBS)

interactive: $(ALL_OBJS)
	$(CC) -L$(RPATH) -Wl,-rpath=$(RPATH) -o interactive $(ALL_OBJS) $(LIBS)


# Remove all object files
.PHONY: clean
clean:
	-find . -type f -name "*.o" -delete

# Sayonara. Viciously destroys all build artifacts, including the executable.
.PHONY: real_clean
real_clean: clean
	-rm $(EXEC_NAME)
