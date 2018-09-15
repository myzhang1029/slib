#!/bin/sh
cat install_manifest.txt | xargs rm 2> /dev/null || true
cat install_manifest.txt | xargs -L1 dirname | xargs rmdir -p 2> /dev/null || true
