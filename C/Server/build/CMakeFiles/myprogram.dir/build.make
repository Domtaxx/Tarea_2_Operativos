# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/build

# Include any dependencies generated for this target.
include CMakeFiles/myprogram.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/myprogram.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/myprogram.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myprogram.dir/flags.make

CMakeFiles/myprogram.dir/Server.c.o: CMakeFiles/myprogram.dir/flags.make
CMakeFiles/myprogram.dir/Server.c.o: ../Server.c
CMakeFiles/myprogram.dir/Server.c.o: CMakeFiles/myprogram.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/myprogram.dir/Server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/myprogram.dir/Server.c.o -MF CMakeFiles/myprogram.dir/Server.c.o.d -o CMakeFiles/myprogram.dir/Server.c.o -c /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/Server.c

CMakeFiles/myprogram.dir/Server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/myprogram.dir/Server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/Server.c > CMakeFiles/myprogram.dir/Server.c.i

CMakeFiles/myprogram.dir/Server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/myprogram.dir/Server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/Server.c -o CMakeFiles/myprogram.dir/Server.c.s

CMakeFiles/myprogram.dir/hist_equa.c.o: CMakeFiles/myprogram.dir/flags.make
CMakeFiles/myprogram.dir/hist_equa.c.o: ../hist_equa.c
CMakeFiles/myprogram.dir/hist_equa.c.o: CMakeFiles/myprogram.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/myprogram.dir/hist_equa.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/myprogram.dir/hist_equa.c.o -MF CMakeFiles/myprogram.dir/hist_equa.c.o.d -o CMakeFiles/myprogram.dir/hist_equa.c.o -c /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/hist_equa.c

CMakeFiles/myprogram.dir/hist_equa.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/myprogram.dir/hist_equa.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/hist_equa.c > CMakeFiles/myprogram.dir/hist_equa.c.i

CMakeFiles/myprogram.dir/hist_equa.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/myprogram.dir/hist_equa.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/hist_equa.c -o CMakeFiles/myprogram.dir/hist_equa.c.s

# Object files for target myprogram
myprogram_OBJECTS = \
"CMakeFiles/myprogram.dir/Server.c.o" \
"CMakeFiles/myprogram.dir/hist_equa.c.o"

# External object files for target myprogram
myprogram_EXTERNAL_OBJECTS =

myprogram: CMakeFiles/myprogram.dir/Server.c.o
myprogram: CMakeFiles/myprogram.dir/hist_equa.c.o
myprogram: CMakeFiles/myprogram.dir/build.make
myprogram: CMakeFiles/myprogram.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable myprogram"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myprogram.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myprogram.dir/build: myprogram
.PHONY : CMakeFiles/myprogram.dir/build

CMakeFiles/myprogram.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myprogram.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myprogram.dir/clean

CMakeFiles/myprogram.dir/depend:
	cd /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/build /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/build /home/domtaxx/Documents/Git/Tarea_2_Operativos/C/Server/build/CMakeFiles/myprogram.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myprogram.dir/depend
