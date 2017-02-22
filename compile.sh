#!/bin/bash

brew install sfml
g++ main.cpp -o adventure -lsfml-system -lsfml-graphics -lsfml-window
./adventure
