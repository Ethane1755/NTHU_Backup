#!/bin/sh
set -e
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/ethanehsieh/documents/CODE/allegro-test/build/demos/cosmic_protector
  /opt/homebrew/bin/cmake -E copy /Users/ethanehsieh/downloads/allegro/demos/cosmic_protector/data/gfx/background.jpg /Users/ethanehsieh/documents/CODE/allegro-test/build/demos/cosmic_protector/data/gfx/background.jpg
fi

