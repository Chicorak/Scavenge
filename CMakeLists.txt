cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(Scavenge)

# Set this to the minimal version you want to support
find_package(raylib 4.0 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

        # build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

    endif()

endif()

# This is the main part:

add_executable(${PROJECT_NAME} src/main.cpp src/GameObject.cpp include/GameObject.hpp src/player.cpp include/player.hpp)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)