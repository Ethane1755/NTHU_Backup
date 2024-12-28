# Install script for directory: /Users/ethanehsieh/downloads/allegro/addons

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

set(CMAKE_BINARY_DIR "/Users/ethanehsieh/documents/CODE/allegro-test/build")

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/primitives/cmake_install.cmake")
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/image/cmake_install.cmake")
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/font/cmake_install.cmake")
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/audio/cmake_install.cmake")
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/acodec/cmake_install.cmake")
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/ttf/cmake_install.cmake")
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/color/cmake_install.cmake")
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/memfile/cmake_install.cmake")
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/physfs/cmake_install.cmake")
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/native_dialog/cmake_install.cmake")
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/video/cmake_install.cmake")
  include("/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/main/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/ethanehsieh/documents/CODE/allegro-test/build/addons/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
