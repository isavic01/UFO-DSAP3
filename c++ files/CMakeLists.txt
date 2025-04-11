cmake_minimum_required(VERSION 3.30)
project(project_3)

set(CMAKE_CXX_STANDARD 26)

include_directories(src)
include_directories(data)

add_executable(main
        src/main.cpp
        src/UFO_Sightings.h src/UFO_Sightings.cpp
)
