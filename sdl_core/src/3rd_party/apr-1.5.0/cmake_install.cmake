# Install script for directory: /home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibapr-1.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibapr-1.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibapr-1.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/liblibapr-1.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibapr-1.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibapr-1.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibapr-1.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/libapr-1.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/liblibaprapp-1.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/libaprapp-1.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/libapr-1.pdb")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES
      "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/libapr-1.pdb"
      "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/libaprapp-1.pdb"
      "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/aprapp-1.pdb"
      )
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_allocator.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_atomic.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_dso.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_env.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_errno.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_escape.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_file_info.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_file_io.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_fnmatch.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_general.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_getopt.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_global_mutex.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_hash.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_inherit.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_lib.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_mmap.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_network_io.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_poll.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_pools.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_portable.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_proc_mutex.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_random.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_ring.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_shm.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_signal.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_skiplist.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_strings.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_support.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_tables.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_thread_cond.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_thread_mutex.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_thread_proc.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_thread_rwlock.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_time.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_user.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_version.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/include/apr_want.h"
    "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/apr.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/yocto/work/github/sdl_core/src/3rd_party/apr-1.5.0/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
