#!/bin/sh
set -e
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/ethanehsieh/documents/CODE/allegro-test/build/demos/shooter
  /opt/homebrew/bin/cmake -E copy /Users/ethanehsieh/downloads/allegro/demos/shooter/data/ENGINE4.png /Users/ethanehsieh/documents/CODE/allegro-test/build/demos/shooter/data/ENGINE4.png
fi

