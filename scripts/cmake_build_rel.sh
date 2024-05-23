#!/usr/bin/env bash

/usr/bin/cmake  --build ./build/release \
                --config Release \
                --target all \
                -j 18
