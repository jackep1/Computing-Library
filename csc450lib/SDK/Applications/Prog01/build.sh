#!/bin/bash

g++ -std=c++20 -I ../../Headers ../../../Development/Sources/*.cpp main.cpp -o prog01
# excluding -Wall for now