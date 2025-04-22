cmake_minimum_required(VERSION 3.10)
project(UFO_Backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
include_directories(
  ${CMAKE_SOURCE_DIR}/external/pistache/include
  ${CMAKE_SOURCE_DIR}/external/libevent/include
)


link_directories(
  ${CMAKE_SOURCE_DIR}/external/pistache/build/src
  ${CMAKE_SOURCE_DIR}/external/libevent/build/lib
)

add_executable(ufo_server
  src/main.cpp
  src/UFO_Sightings.cpp
)


target_link_libraries(ufo_server
  ${CMAKE_SOURCE_DIR}/external/pistache/build/src/libpistache.a
  ${CMAKE_SOURCE_DIR}/external/libevent/build/lib/libevent.a
  ${CMAKE_SOURCE_DIR}/external/libevent/build/lib/libevent_pthreads.a
  pthread
)
