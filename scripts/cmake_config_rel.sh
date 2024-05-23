#!/usr/bin/env bash

/usr/bin/cmake  -DCMAKE_BUILD_TYPE:STRING=Release \
                -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
                -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc \
                -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
                -S "." \
                -B "./build/release" \
                -G "Unix Makefiles"