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
CMAKE_SOURCE_DIR = /home/immariav/ABC-for-simulation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/immariav/ABC-for-simulation/build

# Include any dependencies generated for this target.
include CMakeFiles/ABC-for-simulation.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ABC-for-simulation.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ABC-for-simulation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ABC-for-simulation.dir/flags.make

CMakeFiles/ABC-for-simulation.dir/src/main.cpp.o: CMakeFiles/ABC-for-simulation.dir/flags.make
CMakeFiles/ABC-for-simulation.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/ABC-for-simulation.dir/src/main.cpp.o: CMakeFiles/ABC-for-simulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/immariav/ABC-for-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ABC-for-simulation.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ABC-for-simulation.dir/src/main.cpp.o -MF CMakeFiles/ABC-for-simulation.dir/src/main.cpp.o.d -o CMakeFiles/ABC-for-simulation.dir/src/main.cpp.o -c /home/immariav/ABC-for-simulation/src/main.cpp

CMakeFiles/ABC-for-simulation.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ABC-for-simulation.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/immariav/ABC-for-simulation/src/main.cpp > CMakeFiles/ABC-for-simulation.dir/src/main.cpp.i

CMakeFiles/ABC-for-simulation.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ABC-for-simulation.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/immariav/ABC-for-simulation/src/main.cpp -o CMakeFiles/ABC-for-simulation.dir/src/main.cpp.s

CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.o: CMakeFiles/ABC-for-simulation.dir/flags.make
CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.o: ../src/Bee.cpp
CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.o: CMakeFiles/ABC-for-simulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/immariav/ABC-for-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.o -MF CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.o.d -o CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.o -c /home/immariav/ABC-for-simulation/src/Bee.cpp

CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/immariav/ABC-for-simulation/src/Bee.cpp > CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.i

CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/immariav/ABC-for-simulation/src/Bee.cpp -o CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.s

CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.o: CMakeFiles/ABC-for-simulation.dir/flags.make
CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.o: ../src/EmployedBee.cpp
CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.o: CMakeFiles/ABC-for-simulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/immariav/ABC-for-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.o -MF CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.o.d -o CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.o -c /home/immariav/ABC-for-simulation/src/EmployedBee.cpp

CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/immariav/ABC-for-simulation/src/EmployedBee.cpp > CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.i

CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/immariav/ABC-for-simulation/src/EmployedBee.cpp -o CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.s

CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.o: CMakeFiles/ABC-for-simulation.dir/flags.make
CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.o: ../src/OnlookerBee.cpp
CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.o: CMakeFiles/ABC-for-simulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/immariav/ABC-for-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.o -MF CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.o.d -o CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.o -c /home/immariav/ABC-for-simulation/src/OnlookerBee.cpp

CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/immariav/ABC-for-simulation/src/OnlookerBee.cpp > CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.i

CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/immariav/ABC-for-simulation/src/OnlookerBee.cpp -o CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.s

CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.o: CMakeFiles/ABC-for-simulation.dir/flags.make
CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.o: ../src/FoodSource.cpp
CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.o: CMakeFiles/ABC-for-simulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/immariav/ABC-for-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.o -MF CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.o.d -o CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.o -c /home/immariav/ABC-for-simulation/src/FoodSource.cpp

CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/immariav/ABC-for-simulation/src/FoodSource.cpp > CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.i

CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/immariav/ABC-for-simulation/src/FoodSource.cpp -o CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.s

CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.o: CMakeFiles/ABC-for-simulation.dir/flags.make
CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.o: ../src/Hive.cpp
CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.o: CMakeFiles/ABC-for-simulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/immariav/ABC-for-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.o -MF CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.o.d -o CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.o -c /home/immariav/ABC-for-simulation/src/Hive.cpp

CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/immariav/ABC-for-simulation/src/Hive.cpp > CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.i

CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/immariav/ABC-for-simulation/src/Hive.cpp -o CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.s

# Object files for target ABC-for-simulation
ABC__for__simulation_OBJECTS = \
"CMakeFiles/ABC-for-simulation.dir/src/main.cpp.o" \
"CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.o" \
"CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.o" \
"CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.o" \
"CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.o" \
"CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.o"

# External object files for target ABC-for-simulation
ABC__for__simulation_EXTERNAL_OBJECTS =

ABC-for-simulation: CMakeFiles/ABC-for-simulation.dir/src/main.cpp.o
ABC-for-simulation: CMakeFiles/ABC-for-simulation.dir/src/Bee.cpp.o
ABC-for-simulation: CMakeFiles/ABC-for-simulation.dir/src/EmployedBee.cpp.o
ABC-for-simulation: CMakeFiles/ABC-for-simulation.dir/src/OnlookerBee.cpp.o
ABC-for-simulation: CMakeFiles/ABC-for-simulation.dir/src/FoodSource.cpp.o
ABC-for-simulation: CMakeFiles/ABC-for-simulation.dir/src/Hive.cpp.o
ABC-for-simulation: CMakeFiles/ABC-for-simulation.dir/build.make
ABC-for-simulation: CMakeFiles/ABC-for-simulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/immariav/ABC-for-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ABC-for-simulation"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ABC-for-simulation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ABC-for-simulation.dir/build: ABC-for-simulation
.PHONY : CMakeFiles/ABC-for-simulation.dir/build

CMakeFiles/ABC-for-simulation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ABC-for-simulation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ABC-for-simulation.dir/clean

CMakeFiles/ABC-for-simulation.dir/depend:
	cd /home/immariav/ABC-for-simulation/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/immariav/ABC-for-simulation /home/immariav/ABC-for-simulation /home/immariav/ABC-for-simulation/build /home/immariav/ABC-for-simulation/build /home/immariav/ABC-for-simulation/build/CMakeFiles/ABC-for-simulation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ABC-for-simulation.dir/depend
