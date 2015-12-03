#execute_process(
#  COMMAND ${CMAKE_SOURCE_DIR}/FindQt.sh -v ${qt_version} Qt5CoreConfig.cmake
#  OUTPUT_VARIABLE config_file
#)

set(config_file "/home/yocto/work/yocto/fsl-release-bsp/build/tmp/work/cortexa9hf-vfp-neon-mx6qdl-poky-linux-gnueabi/qtbase/5.3.2-r0/packages-split/qtbase-dev/usr/lib/cmake/Qt5Core/Qt5CoreConfig.cmake")
if(config_file STREQUAL "")
  message(FATAL_ERROR "Qt5 Core module not found")
endif(config_file STREQUAL "")

include(${config_file})
