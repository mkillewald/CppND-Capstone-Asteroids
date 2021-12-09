cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS} -pthread")

project(Asteroids)

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable
add_executable(Asteroids ${project_SRCS})

# For finding our SDL2 package!
INCLUDE(FindPkgConfig)

# Searching SDL2 packages.
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

# Including our external library's directory for header files!
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

# Linking SDL2 library with our project.
target_link_libraries(Asteroids ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})