#!/bin/sh
set -e
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/ethanehsieh/documents/CODE/allegro-test/build/demos/cosmic_protector
  /opt/homebrew/bin/cmake -E copy /Users/ethanehsieh/downloads/allegro/demos/cosmic_protector/data/gfx/large_asteroid.png /Users/ethanehsieh/documents/CODE/allegro-test/build/demos/cosmic_protector/data/gfx/large_asteroid.png
fi
