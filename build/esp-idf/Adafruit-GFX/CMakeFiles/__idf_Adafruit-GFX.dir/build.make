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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/naveenvivek/esp/hyper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/naveenvivek/esp/hyper/build

# Include any dependencies generated for this target.
include esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/depend.make

# Include the progress variables for this target.
include esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/flags.make

esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.obj: esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/flags.make
esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.obj: /Users/naveenvivek/esp/esp-idf/components/Adafruit-GFX/Adafruit_GFX.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/naveenvivek/esp/hyper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.obj"
	cd /Users/naveenvivek/esp/hyper/build/esp-idf/Adafruit-GFX && /Users/naveenvivek/.espressif/tools/xtensa-esp32-elf/esp-2021r2-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.obj -c /Users/naveenvivek/esp/esp-idf/components/Adafruit-GFX/Adafruit_GFX.cpp

esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.i"
	cd /Users/naveenvivek/esp/hyper/build/esp-idf/Adafruit-GFX && /Users/naveenvivek/.espressif/tools/xtensa-esp32-elf/esp-2021r2-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/naveenvivek/esp/esp-idf/components/Adafruit-GFX/Adafruit_GFX.cpp > CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.i

esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.s"
	cd /Users/naveenvivek/esp/hyper/build/esp-idf/Adafruit-GFX && /Users/naveenvivek/.espressif/tools/xtensa-esp32-elf/esp-2021r2-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/naveenvivek/esp/esp-idf/components/Adafruit-GFX/Adafruit_GFX.cpp -o CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.s

# Object files for target __idf_Adafruit-GFX
__idf_Adafruit__GFX_OBJECTS = \
"CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.obj"

# External object files for target __idf_Adafruit-GFX
__idf_Adafruit__GFX_EXTERNAL_OBJECTS =

esp-idf/Adafruit-GFX/libAdafruit-GFX.a: esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/Adafruit_GFX.cpp.obj
esp-idf/Adafruit-GFX/libAdafruit-GFX.a: esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/build.make
esp-idf/Adafruit-GFX/libAdafruit-GFX.a: esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/naveenvivek/esp/hyper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libAdafruit-GFX.a"
	cd /Users/naveenvivek/esp/hyper/build/esp-idf/Adafruit-GFX && $(CMAKE_COMMAND) -P CMakeFiles/__idf_Adafruit-GFX.dir/cmake_clean_target.cmake
	cd /Users/naveenvivek/esp/hyper/build/esp-idf/Adafruit-GFX && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_Adafruit-GFX.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/build: esp-idf/Adafruit-GFX/libAdafruit-GFX.a

.PHONY : esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/build

esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/clean:
	cd /Users/naveenvivek/esp/hyper/build/esp-idf/Adafruit-GFX && $(CMAKE_COMMAND) -P CMakeFiles/__idf_Adafruit-GFX.dir/cmake_clean.cmake
.PHONY : esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/clean

esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/depend:
	cd /Users/naveenvivek/esp/hyper/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/naveenvivek/esp/hyper /Users/naveenvivek/esp/esp-idf/components/Adafruit-GFX /Users/naveenvivek/esp/hyper/build /Users/naveenvivek/esp/hyper/build/esp-idf/Adafruit-GFX /Users/naveenvivek/esp/hyper/build/esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/Adafruit-GFX/CMakeFiles/__idf_Adafruit-GFX.dir/depend
