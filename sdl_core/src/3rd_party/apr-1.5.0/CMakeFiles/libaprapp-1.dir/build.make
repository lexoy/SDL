# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0

# Include any dependencies generated for this target.
include CMakeFiles/libaprapp-1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libaprapp-1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libaprapp-1.dir/flags.make

CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o: CMakeFiles/libaprapp-1.dir/flags.make
CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o: misc/win32/apr_app.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o   -c /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/misc/win32/apr_app.c

CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/misc/win32/apr_app.c > CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.i

CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/misc/win32/apr_app.c -o CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.s

CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o.requires:
.PHONY : CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o.requires

CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o.provides: CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o.requires
	$(MAKE) -f CMakeFiles/libaprapp-1.dir/build.make CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o.provides.build
.PHONY : CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o.provides

CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o.provides.build: CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o

CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o: CMakeFiles/libaprapp-1.dir/flags.make
CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o: misc/win32/internal.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o   -c /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/misc/win32/internal.c

CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/misc/win32/internal.c > CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.i

CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/misc/win32/internal.c -o CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.s

CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o.requires:
.PHONY : CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o.requires

CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o.provides: CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o.requires
	$(MAKE) -f CMakeFiles/libaprapp-1.dir/build.make CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o.provides.build
.PHONY : CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o.provides

CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o.provides.build: CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o

# Object files for target libaprapp-1
libaprapp__1_OBJECTS = \
"CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o" \
"CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o"

# External object files for target libaprapp-1
libaprapp__1_EXTERNAL_OBJECTS =

liblibaprapp-1.a: CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o
liblibaprapp-1.a: CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o
liblibaprapp-1.a: CMakeFiles/libaprapp-1.dir/build.make
liblibaprapp-1.a: CMakeFiles/libaprapp-1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library liblibaprapp-1.a"
	$(CMAKE_COMMAND) -P CMakeFiles/libaprapp-1.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libaprapp-1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libaprapp-1.dir/build: liblibaprapp-1.a
.PHONY : CMakeFiles/libaprapp-1.dir/build

CMakeFiles/libaprapp-1.dir/requires: CMakeFiles/libaprapp-1.dir/misc/win32/apr_app.c.o.requires
CMakeFiles/libaprapp-1.dir/requires: CMakeFiles/libaprapp-1.dir/misc/win32/internal.c.o.requires
.PHONY : CMakeFiles/libaprapp-1.dir/requires

CMakeFiles/libaprapp-1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libaprapp-1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libaprapp-1.dir/clean

CMakeFiles/libaprapp-1.dir/depend:
	cd /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0 /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0 /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0 /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0 /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/CMakeFiles/libaprapp-1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libaprapp-1.dir/depend

