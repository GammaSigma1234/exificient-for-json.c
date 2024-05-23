cmake_minimum_required(VERSION 3.22.0)
project(Exificient_EXI2JSON_experiments VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()

set(CoDec_SOURCE_DIR  src)
set(MY_SOURCE_DIR     test_GS)
set(CORE_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/DecoderChannel.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/EXIHeaderDecoder.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/BitInputStream.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/EncoderChannel.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/EXIHeaderEncoder.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/MethodsBag.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/BitOutputStream.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/EXIforJSONEXIEncoder.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/EXIforJSONEXIDecoder.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/DynamicMemory.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/EXIforJSONEXICoder.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/EXIforJSONQNames.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/StringValueTable.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec/StringNameTable.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/exiforjson/EXIforJSONDecoder.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/exiforjson/EXIforJSONEncoder.c
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/json/jsmn.c
)

# Build both the publisher and the subscriber

add_executable(simple_example
  ${CMAKE_SOURCE_DIR}/${MY_SOURCE_DIR}/simple_example.c
  ${CORE_SOURCE_FILES}
  )

  add_executable(test
  ${CMAKE_SOURCE_DIR}/${MY_SOURCE_DIR}/test.c
  ${CORE_SOURCE_FILES}
)

# Include directories both for the publisher and the subscriber

target_include_directories(simple_example PRIVATE
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/exiforjson
  ${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/json
)

target_include_directories(test PRIVATE
${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/codec
${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/exiforjson
${CMAKE_SOURCE_DIR}/${CoDec_SOURCE_DIR}/json
)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
