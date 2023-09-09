#!/bin/bash

PROJECT_DIR="../"
BUILD_DIR="${PROJECT_DIR}build/"

if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR"
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cd -

echo "> Configuration and build process successful"
echo "> Press any key to close the window"
# Wait for input from the user
read -n 1 -s -r -p ""