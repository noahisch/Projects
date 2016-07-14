## EECS 281 Advanced Makefile

# How to use this Makefile...
###################
###################
##               ##
##  $ make help  ##
##               ##
###################
###################

# IMPORTANT NOTES:
#   1. Set EXECUTABLE to the command name given in the project specification.
#   2. To enable automatic creation of unit test rules, your program logic
#      (where main() is) should be in a file named project*.cpp or specified
#      in the PROJECTFILE variable.
#   3. Files you want to include in your final submission cannot match the
#      test*.cpp pattern.

# Version 4 - 2015-05-03, Marcus M. Darden (mmdarden@umich.edu)
#   * Updated build rules for tests
# Version 3.0.1 - 2015-01-22, Waleed Khan (wkhan@umich.edu)
#   * Added '$(EXECUTABLE): $(OBJECTS)' target. Now you can compile with
#     'make executable', and re-linking isn't done unnecessarily.
# Version 3 - 2015-01-16, Marcus M. Darden (mmdarden@umich.edu)
#   * Add help rule and message
#   * All customization locations are cleary marked.
# Version 2 - 2014-11-02, Marcus M. Darden (mmdarden@umich.edu)
#   * Move customization section to the bottom of the file
#   * Add support for submit without test cases, to prevent submission
#     deduction while testing, when code fails to compile
#       usage: make partialsubmit  <- includes no test case files
#              make fullsubmit     <- includes all test case files
#   * Add automatic creation of test targets for test driver files
#       usage: (add cpp files to the project folder with a test prefix)
#              make alltests       <- builds all test*.cpp
#              make test_insert    <- builds testinsert from test_insert.cpp
#              make test2          <- builds testinsert from test2.cpp
#   * Add documentation and changelog
# Version 1 - 2014-09-21, David Snider (sniderdj@umich.edu)
# Vertion 0 - ????-??-??, Matt Diffenderfer (mjdiffy@umich.edu)

# enables c++14 on CAEN
PATH := /usr/um/gcc-5.1.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-5.1.0/lib64
LD_RUN_PATH := /usr/um/gcc-5.1.0/lib64

# Change EXECUTABLE to match the command name given in the project spec.
EXECUTABLE 	= test

# designate which compiler to use
CXX			= g++

# list of test drivers (with main()) for development
TESTSOURCES = $(wildcard test*.cpp)
# names of test executables
TESTS       = $(TESTSOURCES:%.cpp=%)

# list of sources used in project
SOURCES 	= $(wildcard *.cpp)
SOURCES     := $(filter-out $(TESTSOURCES), $(SOURCES))
# list of objects used in project
OBJECTS		= $(SOURCES:%.cpp=%.o)

PROJECTFILE = sequentialPushRelabel.cpp

# name of the tar ball created for submission
PARTIAL_SUBMITFILE = partialsubmit.tar.gz
FULL_SUBMITFILE = fullsubmit.tar.gz

#Default Flags
CXXFLAGS = -std=c++14 -Wall -Werror -Wextra -pedantic 

# make release - will compile "all" with $(CXXFLAGS) and the -O3 flag
#				 also defines NDEBUG so that asserts will not check
release: CXXFLAGS += -O3 -DNDEBUG
release: all

# make debug - will compile "all" with $(CXXFLAGS) and the -g flag
#              also defines DEBUG so that "#ifdef DEBUG /*...*/ #endif" works
debug: CXXFLAGS += -g3 -DDEBUG
debug: clean all

# make profile - will compile "all" with $(CXXFLAGS) and the -pg flag
profile: CXXFLAGS += -pg
profile: clean all

# highest target; sews together all objects into executable
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
ifeq ($(EXECUTABLE), executable)
	@echo Edit EXECUTABLE variable in Makefile.
	@echo Using default a.out.
	$(CXX) $(CXXFLAGS) $(OBJECTS)
else
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)
endif

# rule for creating objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp

# make clean - remove .o files, executables, tarball
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TESTS) $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE)

sequentialPushRelabel.o: Vertex.o Edge.o sequentialPushRelabel.cpp

Vertex.o: Vertex.cpp Vertex.h Edge.h
Edge.o: Edge.cpp Edge.h

######################
# TODO (end) #
######################

# these targets do not create any files
.PHONY: all release debug profile clean alltests partialsubmit fullsubmit help
# disable built-in rules
.SUFFIXES:
