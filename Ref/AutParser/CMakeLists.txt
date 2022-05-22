# set minimum cmake version
cmake_minimum_required(VERSION 3.9)

# project name and language
project(AutParser)

set(CMAKE_CXX_STANDARD 11)

add_library(autparser-share SHARED ${PROJECT_SOURCE_DIR}/autparser.cpp)

set_target_properties(autparser-share
  PROPERTIES
    OUTPUT_NAME "autparser"
  )

add_executable(autTest autTest.cpp)
target_link_libraries(autTest autparser-share)