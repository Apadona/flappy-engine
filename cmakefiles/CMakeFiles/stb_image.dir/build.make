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
CMAKE_SOURCE_DIR = E:\Barnamenevisi\Prozhe_ha\Man\engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Barnamenevisi\Prozhe_ha\Man\engine\cmakefiles

# Include any dependencies generated for this target.
include CMakeFiles/stb_image.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/stb_image.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/stb_image.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stb_image.dir/flags.make

CMakeFiles/stb_image.dir/dependencies/stb_image/stb_image.cpp.obj: CMakeFiles/stb_image.dir/flags.make
CMakeFiles/stb_image.dir/dependencies/stb_image/stb_image.cpp.obj: ../dependencies/stb_image/stb_image.cpp
CMakeFiles/stb_image.dir/dependencies/stb_image/stb_image.cpp.obj: CMakeFiles/stb_image.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Barnamenevisi\Prozhe_ha\Man\engine\cmakefiles\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stb_image.dir/dependencies/stb_image/stb_image.cpp.obj"
	"E:\Barnamenevisi\abzar ha\c++\Compiler\MinGW(7.3.0)\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stb_image.dir/dependencies/stb_image/stb_image.cpp.obj -MF CMakeFiles\stb_image.dir\dependencies\stb_image\stb_image.cpp.obj.d -o CMakeFiles\stb_image.dir\dependencies\stb_image\stb_image.cpp.obj -c E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\stb_image\stb_image.cpp

CMakeFiles/stb_image.dir/dependencies/stb_image/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stb_image.dir/dependencies/stb_image/stb_image.cpp.i"
	"E:\Barnamenevisi\abzar ha\c++\Compiler\MinGW(7.3.0)\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\stb_image\stb_image.cpp > CMakeFiles\stb_image.dir\dependencies\stb_image\stb_image.cpp.i

CMakeFiles/stb_image.dir/dependencies/stb_image/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stb_image.dir/dependencies/stb_image/stb_image.cpp.s"
	"E:\Barnamenevisi\abzar ha\c++\Compiler\MinGW(7.3.0)\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Barnamenevisi\Prozhe_ha\Man\engine\dependencies\stb_image\stb_image.cpp -o CMakeFiles\stb_image.dir\dependencies\stb_image\stb_image.cpp.s

# Object files for target stb_image
stb_image_OBJECTS = \
"CMakeFiles/stb_image.dir/dependencies/stb_image/stb_image.cpp.obj"

# External object files for target stb_image
stb_image_EXTERNAL_OBJECTS =

../build/lib/libstb_image.a: CMakeFiles/stb_image.dir/dependencies/stb_image/stb_image.cpp.obj
../build/lib/libstb_image.a: CMakeFiles/stb_image.dir/build.make
../build/lib/libstb_image.a: CMakeFiles/stb_image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Barnamenevisi\Prozhe_ha\Man\engine\cmakefiles\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\build\lib\libstb_image.a"
	$(CMAKE_COMMAND) -P CMakeFiles\stb_image.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\stb_image.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stb_image.dir/build: ../build/lib/libstb_image.a
.PHONY : CMakeFiles/stb_image.dir/build

CMakeFiles/stb_image.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\stb_image.dir\cmake_clean.cmake
.PHONY : CMakeFiles/stb_image.dir/clean

CMakeFiles/stb_image.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Barnamenevisi\Prozhe_ha\Man\engine E:\Barnamenevisi\Prozhe_ha\Man\engine E:\Barnamenevisi\Prozhe_ha\Man\engine\cmakefiles E:\Barnamenevisi\Prozhe_ha\Man\engine\cmakefiles E:\Barnamenevisi\Prozhe_ha\Man\engine\cmakefiles\CMakeFiles\stb_image.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stb_image.dir/depend

