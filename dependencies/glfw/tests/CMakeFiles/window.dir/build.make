# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Barnamenevisi\abzar ha\Cmake\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Barnamenevisi\abzar ha\Cmake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw

# Include any dependencies generated for this target.
include tests/CMakeFiles/window.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/window.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/window.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/window.dir/flags.make

tests/CMakeFiles/window.dir/window.c.obj: tests/CMakeFiles/window.dir/flags.make
tests/CMakeFiles/window.dir/window.c.obj: tests/CMakeFiles/window.dir/includes_C.rsp
tests/CMakeFiles/window.dir/window.c.obj: tests/window.c
tests/CMakeFiles/window.dir/window.c.obj: tests/CMakeFiles/window.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/window.dir/window.c.obj"
	cd /d E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\tests && "E:\Barnamenevisi\abzar ha\c++\Compiler\MinGW(7.3.0)\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/window.dir/window.c.obj -MF CMakeFiles\window.dir\window.c.obj.d -o CMakeFiles\window.dir\window.c.obj -c E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\tests\window.c

tests/CMakeFiles/window.dir/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/window.dir/window.c.i"
	cd /d E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\tests && "E:\Barnamenevisi\abzar ha\c++\Compiler\MinGW(7.3.0)\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\tests\window.c > CMakeFiles\window.dir\window.c.i

tests/CMakeFiles/window.dir/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/window.dir/window.c.s"
	cd /d E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\tests && "E:\Barnamenevisi\abzar ha\c++\Compiler\MinGW(7.3.0)\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\tests\window.c -o CMakeFiles\window.dir\window.c.s

# Object files for target window
window_OBJECTS = \
"CMakeFiles/window.dir/window.c.obj"

# External object files for target window
window_EXTERNAL_OBJECTS =

tests/window.exe: tests/CMakeFiles/window.dir/window.c.obj
tests/window.exe: tests/CMakeFiles/window.dir/build.make
tests/window.exe: src/libglfw3.a
tests/window.exe: tests/CMakeFiles/window.dir/linklibs.rsp
tests/window.exe: tests/CMakeFiles/window.dir/objects1.rsp
tests/window.exe: tests/CMakeFiles/window.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable window.exe"
	cd /d E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\window.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/window.dir/build: tests/window.exe
.PHONY : tests/CMakeFiles/window.dir/build

tests/CMakeFiles/window.dir/clean:
	cd /d E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\tests && $(CMAKE_COMMAND) -P CMakeFiles\window.dir\cmake_clean.cmake
.PHONY : tests/CMakeFiles/window.dir/clean

tests/CMakeFiles/window.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\tests E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\tests E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\glfw\tests\CMakeFiles\window.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/window.dir/depend

