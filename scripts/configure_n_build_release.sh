#!bin/bash

echo "> Starting the configuration of the project via a bash script"
echo "> Mode: configure and build release"
echo ""

cd ..
mkdir build
cd build
cmake ..
cmake -DCMAKE_BUILD_TYPE=Release .

echo "> Configuration of the project ended"

echo ""
echo "> Press any key to close the window"
# Wait for input from the user
read -n 1 -s -r -p ""

# The script will stay open until the user presses a key
