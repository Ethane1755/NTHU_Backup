#!/bin/sh
set -e
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/ethanehsieh/documents/CODE/allegro-test/build
  /opt/homebrew/bin/cmake -E copy /Users/ethanehsieh/downloads/allegro/examples/data/DejaVuSans.ttf /Users/ethanehsieh/documents/CODE/allegro-test/build/examples/data/DejaVuSans.ttf
fi

