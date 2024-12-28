#!/bin/sh
set -e
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/ethanehsieh/documents/CODE/allegro-test/build/demos/shooter
  /opt/homebrew/bin/cmake -E copy /Users/ethanehsieh/downloads/allegro/demos/shooter/data/ROCKET.png /Users/ethanehsieh/documents/CODE/allegro-test/build/demos/shooter/data/ROCKET.png
fi

