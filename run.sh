#!/bin/bash

# compiling the cpp file
g++ -o snaildb src/main.cpp

if [ $? -eq 0 ]; then
    echo "Compilation [SUCCESS]"
    echo "Starting SnailDB 🐌🐌🐌"
    ./snaildb
else 
    echo "Compilation [FAILED]"
    echo "Checkout the errors."
fi