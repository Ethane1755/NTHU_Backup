#!/bin/sh
set -e
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/ethanehsieh/documents/CODE/allegro-test/build/demos/skater
  /opt/homebrew/bin/cmake -E copy /Users/ethanehsieh/downloads/allegro/demos/skater/data/graphics/ice.png /Users/ethanehsieh/documents/CODE/allegro-test/build/demos/skater/data/graphics/ice.png
fi
