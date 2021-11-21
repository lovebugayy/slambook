project(useEigen)

cmake_minimum_required(VERSION 2.8)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(useEigen  main.cpp coordinateTransform.cpp)