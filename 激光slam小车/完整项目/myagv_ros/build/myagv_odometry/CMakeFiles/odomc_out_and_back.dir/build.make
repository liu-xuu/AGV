# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /home/ubuntu/cmake-3.19.8-Linux-aarch64/bin/cmake

# The command to remove a file.
RM = /home/ubuntu/cmake-3.19.8-Linux-aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/myagv_ros/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/myagv_ros/build

# Include any dependencies generated for this target.
include myagv_odometry/CMakeFiles/odomc_out_and_back.dir/depend.make

# Include the progress variables for this target.
include myagv_odometry/CMakeFiles/odomc_out_and_back.dir/progress.make

# Include the compile flags for this target's objects.
include myagv_odometry/CMakeFiles/odomc_out_and_back.dir/flags.make

myagv_odometry/CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.o: myagv_odometry/CMakeFiles/odomc_out_and_back.dir/flags.make
myagv_odometry/CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.o: /home/ubuntu/myagv_ros/src/myagv_odometry/src/odomc_out_and_back.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/myagv_ros/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object myagv_odometry/CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.o"
	cd /home/ubuntu/myagv_ros/build/myagv_odometry && /usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.o -c /home/ubuntu/myagv_ros/src/myagv_odometry/src/odomc_out_and_back.cpp

myagv_odometry/CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.i"
	cd /home/ubuntu/myagv_ros/build/myagv_odometry && /usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/myagv_ros/src/myagv_odometry/src/odomc_out_and_back.cpp > CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.i

myagv_odometry/CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.s"
	cd /home/ubuntu/myagv_ros/build/myagv_odometry && /usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/myagv_ros/src/myagv_odometry/src/odomc_out_and_back.cpp -o CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.s

# Object files for target odomc_out_and_back
odomc_out_and_back_OBJECTS = \
"CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.o"

# External object files for target odomc_out_and_back
odomc_out_and_back_EXTERNAL_OBJECTS =

/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: myagv_odometry/CMakeFiles/odomc_out_and_back.dir/src/odomc_out_and_back.cpp.o
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: myagv_odometry/CMakeFiles/odomc_out_and_back.dir/build.make
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/libtf.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/libtf2_ros.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/libactionlib.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/libmessage_filters.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/libroscpp.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /usr/lib/aarch64-linux-gnu/libboost_filesystem.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/libxmlrpcpp.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/libtf2.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/libroscpp_serialization.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/librosconsole.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/librosconsole_log4cxx.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/librosconsole_backend_interface.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /usr/lib/aarch64-linux-gnu/liblog4cxx.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /usr/lib/aarch64-linux-gnu/libboost_regex.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/librostime.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /opt/ros/melodic/lib/libcpp_common.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /usr/lib/aarch64-linux-gnu/libboost_system.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /usr/lib/aarch64-linux-gnu/libboost_thread.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /usr/lib/aarch64-linux-gnu/libboost_chrono.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /usr/lib/aarch64-linux-gnu/libboost_date_time.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /usr/lib/aarch64-linux-gnu/libboost_atomic.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /usr/lib/aarch64-linux-gnu/libpthread.so
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: /usr/lib/aarch64-linux-gnu/libconsole_bridge.so.0.4
/home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back: myagv_odometry/CMakeFiles/odomc_out_and_back.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/myagv_ros/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back"
	cd /home/ubuntu/myagv_ros/build/myagv_odometry && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/odomc_out_and_back.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
myagv_odometry/CMakeFiles/odomc_out_and_back.dir/build: /home/ubuntu/myagv_ros/devel/lib/myagv_odometry/odomc_out_and_back

.PHONY : myagv_odometry/CMakeFiles/odomc_out_and_back.dir/build

myagv_odometry/CMakeFiles/odomc_out_and_back.dir/clean:
	cd /home/ubuntu/myagv_ros/build/myagv_odometry && $(CMAKE_COMMAND) -P CMakeFiles/odomc_out_and_back.dir/cmake_clean.cmake
.PHONY : myagv_odometry/CMakeFiles/odomc_out_and_back.dir/clean

myagv_odometry/CMakeFiles/odomc_out_and_back.dir/depend:
	cd /home/ubuntu/myagv_ros/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/myagv_ros/src /home/ubuntu/myagv_ros/src/myagv_odometry /home/ubuntu/myagv_ros/build /home/ubuntu/myagv_ros/build/myagv_odometry /home/ubuntu/myagv_ros/build/myagv_odometry/CMakeFiles/odomc_out_and_back.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : myagv_odometry/CMakeFiles/odomc_out_and_back.dir/depend

