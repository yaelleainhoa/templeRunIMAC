# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build

# Include any dependencies generated for this target.
include jeu/CMakeFiles/jeu_SDLtemplate.dir/depend.make

# Include the progress variables for this target.
include jeu/CMakeFiles/jeu_SDLtemplate.dir/progress.make

# Include the compile flags for this target's objects.
include jeu/CMakeFiles/jeu_SDLtemplate.dir/flags.make

jeu/CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.o: jeu/CMakeFiles/jeu_SDLtemplate.dir/flags.make
jeu/CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.o: /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun/jeu/SDLtemplate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object jeu/CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.o"
	cd /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build/jeu && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.o -c /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun/jeu/SDLtemplate.cpp

jeu/CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.i"
	cd /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build/jeu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun/jeu/SDLtemplate.cpp > CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.i

jeu/CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.s"
	cd /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build/jeu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun/jeu/SDLtemplate.cpp -o CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.s

# Object files for target jeu_SDLtemplate
jeu_SDLtemplate_OBJECTS = \
"CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.o"

# External object files for target jeu_SDLtemplate
jeu_SDLtemplate_EXTERNAL_OBJECTS =

jeu/jeu_SDLtemplate: jeu/CMakeFiles/jeu_SDLtemplate.dir/SDLtemplate.cpp.o
jeu/jeu_SDLtemplate: jeu/CMakeFiles/jeu_SDLtemplate.dir/build.make
jeu/jeu_SDLtemplate: glimac/libglimac.a
jeu/jeu_SDLtemplate: /usr/lib/x86_64-linux-gnu/libSDL_ttf.so
jeu/jeu_SDLtemplate: /usr/lib/x86_64-linux-gnu/libSDLmain.a
jeu/jeu_SDLtemplate: /usr/lib/x86_64-linux-gnu/libSDL.so
jeu/jeu_SDLtemplate: /usr/lib/x86_64-linux-gnu/libGL.so
jeu/jeu_SDLtemplate: /usr/lib/x86_64-linux-gnu/libGLU.so
jeu/jeu_SDLtemplate: /usr/lib/x86_64-linux-gnu/libGLEW.so
jeu/jeu_SDLtemplate: jeu/CMakeFiles/jeu_SDLtemplate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable jeu_SDLtemplate"
	cd /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build/jeu && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jeu_SDLtemplate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
jeu/CMakeFiles/jeu_SDLtemplate.dir/build: jeu/jeu_SDLtemplate

.PHONY : jeu/CMakeFiles/jeu_SDLtemplate.dir/build

jeu/CMakeFiles/jeu_SDLtemplate.dir/clean:
	cd /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build/jeu && $(CMAKE_COMMAND) -P CMakeFiles/jeu_SDLtemplate.dir/cmake_clean.cmake
.PHONY : jeu/CMakeFiles/jeu_SDLtemplate.dir/clean

jeu/CMakeFiles/jeu_SDLtemplate.dir/depend:
	cd /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun/jeu /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build/jeu /home/yaelle/Documents/S2/templeRun/templeRunIMAC/templeRun-build/jeu/CMakeFiles/jeu_SDLtemplate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jeu/CMakeFiles/jeu_SDLtemplate.dir/depend

