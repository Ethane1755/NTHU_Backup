#!/bin/sh
set -e
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/ethanehsieh/documents/CODE/allegro-test/build
  /opt/homebrew/bin/cmake -E copy /Users/ethanehsieh/downloads/allegro/examples/data/a4_font.fnt /Users/ethanehsieh/documents/CODE/allegro-test/build/examples/data/a4_font.fnt
fi

