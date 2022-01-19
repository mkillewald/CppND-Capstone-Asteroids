cmake_minimum_required(VERSION 3.7)

set(CXX_FLAGS "-Wall -std=c++17")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS} -pthread")

project(Asteroids C CXX)

# Find all executables
file(GLOB project_SRCS src/*.cpp lib/*.c)

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

add_library(FontCache
    lib/SDL_FontCache.h
    lib/SDL_FontCache.c
)

target_include_directories(FontCache PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(FontCache PUBLIC .)
target_link_libraries(FontCache ${SDL2_LIBRARIES})
target_include_directories(FontCache PUBLIC ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(FontCache ${SDL2TTF_LIBRARIES})
target_link_libraries(Asteroids FontCache)