#!/bin/sh
set -e
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/ethanehsieh/documents/CODE/allegro-test/build/addons/video
  /opt/homebrew/bin/cmake -E cmake_symlink_library /Users/ethanehsieh/documents/CODE/allegro-test/build/lib/RelWithDebInfo/liballegro_video.5.2.10.dylib /Users/ethanehsieh/documents/CODE/allegro-test/build/lib/RelWithDebInfo/liballegro_video.5.2.dylib /Users/ethanehsieh/documents/CODE/allegro-test/build/lib/RelWithDebInfo/liballegro_video.dylib
fi
