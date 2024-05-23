#!/usr/bin/env bash

# Build in Debug configuration, also using some source files from OpenV2G, namely the EXI CoDec portion
gcc ./test_GS/test.c \
    ./src/codec/DecoderChannel.c \
    ./src/codec/EXIHeaderDecoder.c \
    ./src/codec/BitInputStream.c \
    ./src/codec/EncoderChannel.c \
    ./src/codec/EXIHeaderEncoder.c \
    ./src/codec/MethodsBag.c \
    ./src/codec/BitOutputStream.c \
    ./src/exiforjson/EXIforJSONDecoder.c \
    ./src/codec/EXIforJSONEXIDecoder.c \
    ./src/codec/DynamicMemory.c \
    ./src/codec/EXIforJSONEXICoder.c \
    ./src/codec/EXIforJSONQNames.c \
    ./src/codec/StringValueTable.c \
    ./src/codec/StringNameTable.c \
    -I./src/codec \
    -I./src/exiforjson \
    -I./src/json \
    -g3 -O0 \
    -o ./test_GS/test.exe