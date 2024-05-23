#!/usr/bin/env bash

/usr/bin/cmake  --build ./build/debug \
                --config Debug \
                --target all \
                -j 18
