#!/bin/sh
set -e
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/ethanehsieh/documents/CODE/allegro-test/build
  /opt/homebrew/bin/cmake -E copy /Users/ethanehsieh/downloads/allegro/examples/data/haiku/water_droplets.png /Users/ethanehsieh/documents/CODE/allegro-test/build/examples/data/haiku/water_droplets.png
fi
