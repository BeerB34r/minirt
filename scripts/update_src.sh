#!/usr/bin/env sh
cd ..
find src -type f -name "*.c" -printf "%f " > src.list
