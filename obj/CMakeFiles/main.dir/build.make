# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /mnt/hgfs/vm共享/json/json

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/vm共享/json/json

# Include any dependencies generated for this target.
include obj/CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include obj/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include obj/CMakeFiles/main.dir/flags.make

obj/CMakeFiles/main.dir/leptjson.c.o: obj/CMakeFiles/main.dir/flags.make
obj/CMakeFiles/main.dir/leptjson.c.o: obj/leptjson.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/vm共享/json/json/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object obj/CMakeFiles/main.dir/leptjson.c.o"
	cd /mnt/hgfs/vm共享/json/json/obj && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/leptjson.c.o -c /mnt/hgfs/vm共享/json/json/obj/leptjson.c

obj/CMakeFiles/main.dir/leptjson.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/leptjson.c.i"
	cd /mnt/hgfs/vm共享/json/json/obj && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/hgfs/vm共享/json/json/obj/leptjson.c > CMakeFiles/main.dir/leptjson.c.i

obj/CMakeFiles/main.dir/leptjson.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/leptjson.c.s"
	cd /mnt/hgfs/vm共享/json/json/obj && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/hgfs/vm共享/json/json/obj/leptjson.c -o CMakeFiles/main.dir/leptjson.c.s

obj/CMakeFiles/main.dir/test_main.c.o: obj/CMakeFiles/main.dir/flags.make
obj/CMakeFiles/main.dir/test_main.c.o: obj/test_main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/vm共享/json/json/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object obj/CMakeFiles/main.dir/test_main.c.o"
	cd /mnt/hgfs/vm共享/json/json/obj && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/test_main.c.o -c /mnt/hgfs/vm共享/json/json/obj/test_main.c

obj/CMakeFiles/main.dir/test_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/test_main.c.i"
	cd /mnt/hgfs/vm共享/json/json/obj && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/hgfs/vm共享/json/json/obj/test_main.c > CMakeFiles/main.dir/test_main.c.i

obj/CMakeFiles/main.dir/test_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/test_main.c.s"
	cd /mnt/hgfs/vm共享/json/json/obj && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/hgfs/vm共享/json/json/obj/test_main.c -o CMakeFiles/main.dir/test_main.c.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/leptjson.c.o" \
"CMakeFiles/main.dir/test_main.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

bin/main: obj/CMakeFiles/main.dir/leptjson.c.o
bin/main: obj/CMakeFiles/main.dir/test_main.c.o
bin/main: obj/CMakeFiles/main.dir/build.make
bin/main: obj/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/vm共享/json/json/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ../bin/main"
	cd /mnt/hgfs/vm共享/json/json/obj && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
obj/CMakeFiles/main.dir/build: bin/main

.PHONY : obj/CMakeFiles/main.dir/build

obj/CMakeFiles/main.dir/clean:
	cd /mnt/hgfs/vm共享/json/json/obj && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : obj/CMakeFiles/main.dir/clean

obj/CMakeFiles/main.dir/depend:
	cd /mnt/hgfs/vm共享/json/json && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/vm共享/json/json /mnt/hgfs/vm共享/json/json/obj /mnt/hgfs/vm共享/json/json /mnt/hgfs/vm共享/json/json/obj /mnt/hgfs/vm共享/json/json/obj/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : obj/CMakeFiles/main.dir/depend

