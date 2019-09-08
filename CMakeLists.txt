cmake_minimum_required (VERSION 2.8)

project(raspCamCal)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(raspCamCal raspCamCal.cpp)

target_link_libraries(raspCamCal ${OpenCV_LIBS})
