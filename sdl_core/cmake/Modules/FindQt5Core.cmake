#execute_process(
#  COMMAND ${CMAKE_SOURCE_DIR}/FindQt.sh -v ${qt_version} Qt5CoreConfig.cmake
#  OUTPUT_VARIABLE config_file
#)

set(config_file "/opt/poky/1.7/sysroots/cortexa9hf-vfp-neon-poky-linux-gnueabi/usr/lib/cmake/Qt5Core/Qt5CoreConfig.cmake")

if(config_file STREQUAL "")
  message(FATAL_ERROR "Qt5 Core module not found")
endif(config_file STREQUAL "")

include(${config_file})
