project(useEigen)

cmake_minimum_required(VERSION 2.8)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
add_executable(useEigen  main.cpp coordinateTransform.cpp plotTrajectory.cpp)
target_link_libraries(useEigen ${Pangolin_LIBRARIES})


#target_link_directories(useEigen pangolin)
