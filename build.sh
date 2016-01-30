#!/bin/bash

# clears the terminal
#clear

# create build dir if it doesnt exist 
if [ ! -d "build" ]; then
        # Control will enter here if $DIRECTORY doesn't exist.
        mkdir build
        echo Created build directory
fi

# go to build dir
cd build 

# launch the cmake script in parent dir to keep parent dir clean 
cmake ..
# compiles and builds the project
make


