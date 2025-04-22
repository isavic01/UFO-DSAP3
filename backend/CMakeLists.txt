cmake_minimum_required(VERSION 3.14)
project(UFOServer)

set(CMAKE_CXX_STANDARD 17)

# Boost & Threads
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Threads REQUIRED)

# Enable Crow with Boost
set(CROW_USE_BOOST ON)
add_subdirectory(libs/Crow)

# Executable
add_executable(server main.cpp UFO_Sightings.cpp)
target_include_directories(server PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(server PRIVATE Crow::Crow ${Boost_LIBRARIES} Threads::Threads)
