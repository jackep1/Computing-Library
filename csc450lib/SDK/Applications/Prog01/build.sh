#!/bin/bash

g++ -std=c++20 -I ../../Headers ../../Headers/Functions ../../../Development/Sources/*.cpp ../../../Development/Sources/Functions/*.cpp main.cpp -o prog01
# excluding -Wall for now