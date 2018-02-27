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

# enables c++11 on CAEN
PATH := /usr/um/gcc-4.8.3/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.8.3/lib64
LD_RUN_PATH := /usr/um/gcc-4.8.3/lib64

# TODO #
# Change EXECUTABLE to match the command name given in the project spec.
EXECUTABLE 	= logman

# designate which compiler to use
CXX			= g++

# list of sources used in project
SOURCES 	= $(wildcard *.cpp)
SOURCES     := $(filter-out $(TESTSOURCES), $(SOURCES))
# list of objects used in project
OBJECTS		= $(SOURCES:%.cpp=%.o)

# If main() is in a file named project*.cpp, use the following line
#
PROJECTFILE = $(wildcard project1.cpp)

#Default Flags
CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -pedantic

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
	rm -f $(OBJECTS) $(EXECUTABLE)

define MAKEFILE_HELP
Makefile Help

* Commands
	$$ make all
		sews together all objects into executable
	$$ make profile
		will compile "all" with $(CXXFLAGS) and the -pg flag
	$$ make debug
		will compile "all" with $(CXXFLAGS) and the -g flag
	$$ make clean
		removes executable and compiled files

* Executable Support
	This program utilizes input and output redirection.
	Example Command Line Prompt:
		./logman example-log.txt < example-cmds.txt > example-output.txt

endef
export MAKEFILE_HELP

help:
	@echo "$$MAKEFILE_HELP"

# these targets do not create any files
.PHONY: all release debug profile clean alltests partialsubmit fullsubmit help
# disable built-in rules
.SUFFIXES:
