#!/bin/sh
set -e
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/ethanehsieh/documents/CODE/allegro-test/build
  /opt/homebrew/bin/cmake -E copy /Users/ethanehsieh/downloads/allegro/examples/data/mysha_pal.png /Users/ethanehsieh/documents/CODE/allegro-test/build/examples/data/mysha_pal.png
fi
