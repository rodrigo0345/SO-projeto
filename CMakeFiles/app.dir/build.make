# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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

# Include any dependencies generated for this target.
include CMakeFiles/app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/app.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/app.dir/flags.make

CMakeFiles/app.dir/main.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/main.c.o: main.c
CMakeFiles/app.dir/main.c.o: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/rodrigo0345/dev/trabalho-SO/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/app.dir/main.c.o"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/main.c.o -MF CMakeFiles/app.dir/main.c.o.d -o CMakeFiles/app.dir/main.c.o -c /home/rodrigo0345/dev/trabalho-SO/main.c

CMakeFiles/app.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/app.dir/main.c.i"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rodrigo0345/dev/trabalho-SO/main.c > CMakeFiles/app.dir/main.c.i

CMakeFiles/app.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/app.dir/main.c.s"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rodrigo0345/dev/trabalho-SO/main.c -o CMakeFiles/app.dir/main.c.s

CMakeFiles/app.dir/pipes.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/pipes.c.o: pipes.c
CMakeFiles/app.dir/pipes.c.o: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/rodrigo0345/dev/trabalho-SO/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/app.dir/pipes.c.o"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/pipes.c.o -MF CMakeFiles/app.dir/pipes.c.o.d -o CMakeFiles/app.dir/pipes.c.o -c /home/rodrigo0345/dev/trabalho-SO/pipes.c

CMakeFiles/app.dir/pipes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/app.dir/pipes.c.i"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rodrigo0345/dev/trabalho-SO/pipes.c > CMakeFiles/app.dir/pipes.c.i

CMakeFiles/app.dir/pipes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/app.dir/pipes.c.s"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rodrigo0345/dev/trabalho-SO/pipes.c -o CMakeFiles/app.dir/pipes.c.s

CMakeFiles/app.dir/processes.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/processes.c.o: processes.c
CMakeFiles/app.dir/processes.c.o: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/rodrigo0345/dev/trabalho-SO/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/app.dir/processes.c.o"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/processes.c.o -MF CMakeFiles/app.dir/processes.c.o.d -o CMakeFiles/app.dir/processes.c.o -c /home/rodrigo0345/dev/trabalho-SO/processes.c

CMakeFiles/app.dir/processes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/app.dir/processes.c.i"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rodrigo0345/dev/trabalho-SO/processes.c > CMakeFiles/app.dir/processes.c.i

CMakeFiles/app.dir/processes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/app.dir/processes.c.s"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rodrigo0345/dev/trabalho-SO/processes.c -o CMakeFiles/app.dir/processes.c.s

CMakeFiles/app.dir/programs.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/programs.c.o: programs.c
CMakeFiles/app.dir/programs.c.o: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/rodrigo0345/dev/trabalho-SO/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/app.dir/programs.c.o"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/programs.c.o -MF CMakeFiles/app.dir/programs.c.o.d -o CMakeFiles/app.dir/programs.c.o -c /home/rodrigo0345/dev/trabalho-SO/programs.c

CMakeFiles/app.dir/programs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/app.dir/programs.c.i"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rodrigo0345/dev/trabalho-SO/programs.c > CMakeFiles/app.dir/programs.c.i

CMakeFiles/app.dir/programs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/app.dir/programs.c.s"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rodrigo0345/dev/trabalho-SO/programs.c -o CMakeFiles/app.dir/programs.c.s

CMakeFiles/app.dir/strings.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/strings.c.o: strings.c
CMakeFiles/app.dir/strings.c.o: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/rodrigo0345/dev/trabalho-SO/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/app.dir/strings.c.o"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/strings.c.o -MF CMakeFiles/app.dir/strings.c.o.d -o CMakeFiles/app.dir/strings.c.o -c /home/rodrigo0345/dev/trabalho-SO/strings.c

CMakeFiles/app.dir/strings.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/app.dir/strings.c.i"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rodrigo0345/dev/trabalho-SO/strings.c > CMakeFiles/app.dir/strings.c.i

CMakeFiles/app.dir/strings.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/app.dir/strings.c.s"
	/usr/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rodrigo0345/dev/trabalho-SO/strings.c -o CMakeFiles/app.dir/strings.c.s

# Object files for target app
app_OBJECTS = \
"CMakeFiles/app.dir/main.c.o" \
"CMakeFiles/app.dir/pipes.c.o" \
"CMakeFiles/app.dir/processes.c.o" \
"CMakeFiles/app.dir/programs.c.o" \
"CMakeFiles/app.dir/strings.c.o"

# External object files for target app
app_EXTERNAL_OBJECTS =

app: CMakeFiles/app.dir/main.c.o
app: CMakeFiles/app.dir/pipes.c.o
app: CMakeFiles/app.dir/processes.c.o
app: CMakeFiles/app.dir/programs.c.o
app: CMakeFiles/app.dir/strings.c.o
app: CMakeFiles/app.dir/build.make
app: /usr/local/lib/libraylib.so
app: CMakeFiles/app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/rodrigo0345/dev/trabalho-SO/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/app.dir/build: app
.PHONY : CMakeFiles/app.dir/build

CMakeFiles/app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/app.dir/clean

CMakeFiles/app.dir/depend:
	cd /home/rodrigo0345/dev/trabalho-SO && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rodrigo0345/dev/trabalho-SO /home/rodrigo0345/dev/trabalho-SO /home/rodrigo0345/dev/trabalho-SO /home/rodrigo0345/dev/trabalho-SO /home/rodrigo0345/dev/trabalho-SO/CMakeFiles/app.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/app.dir/depend

