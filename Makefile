# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rodrigo0345/dev/trabalho-SO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rodrigo0345/dev/trabalho-SO

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rodrigo0345/dev/trabalho-SO/CMakeFiles /home/rodrigo0345/dev/trabalho-SO//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rodrigo0345/dev/trabalho-SO/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named app

# Build rule for target.
app: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 app
.PHONY : app

# fast build rule for target.
app/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/build
.PHONY : app/fast

main.o: main.c.o
.PHONY : main.o

# target to build an object file
main.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/main.c.o
.PHONY : main.c.o

main.i: main.c.i
.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s
.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/main.c.s
.PHONY : main.c.s

pipes.o: pipes.c.o
.PHONY : pipes.o

# target to build an object file
pipes.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/pipes.c.o
.PHONY : pipes.c.o

pipes.i: pipes.c.i
.PHONY : pipes.i

# target to preprocess a source file
pipes.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/pipes.c.i
.PHONY : pipes.c.i

pipes.s: pipes.c.s
.PHONY : pipes.s

# target to generate assembly for a file
pipes.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/pipes.c.s
.PHONY : pipes.c.s

processes.o: processes.c.o
.PHONY : processes.o

# target to build an object file
processes.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/processes.c.o
.PHONY : processes.c.o

processes.i: processes.c.i
.PHONY : processes.i

# target to preprocess a source file
processes.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/processes.c.i
.PHONY : processes.c.i

processes.s: processes.c.s
.PHONY : processes.s

# target to generate assembly for a file
processes.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/processes.c.s
.PHONY : processes.c.s

programs.o: programs.c.o
.PHONY : programs.o

# target to build an object file
programs.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/programs.c.o
.PHONY : programs.c.o

programs.i: programs.c.i
.PHONY : programs.i

# target to preprocess a source file
programs.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/programs.c.i
.PHONY : programs.c.i

programs.s: programs.c.s
.PHONY : programs.s

# target to generate assembly for a file
programs.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/programs.c.s
.PHONY : programs.c.s

strings.o: strings.c.o
.PHONY : strings.o

# target to build an object file
strings.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/strings.c.o
.PHONY : strings.c.o

strings.i: strings.c.i
.PHONY : strings.i

# target to preprocess a source file
strings.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/strings.c.i
.PHONY : strings.c.i

strings.s: strings.c.s
.PHONY : strings.s

# target to generate assembly for a file
strings.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/strings.c.s
.PHONY : strings.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... app"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... pipes.o"
	@echo "... pipes.i"
	@echo "... pipes.s"
	@echo "... processes.o"
	@echo "... processes.i"
	@echo "... processes.s"
	@echo "... programs.o"
	@echo "... programs.i"
	@echo "... programs.s"
	@echo "... strings.o"
	@echo "... strings.i"
	@echo "... strings.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

