#!/bin/bash
cmake -B build
cmake --build build && build/bin/meltris
