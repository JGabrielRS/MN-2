cmake_minimum_required(VERSION 3.14)
project(MetodosNum2)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(MetodosNum2 ${SRC_FILES})

if(NOT WIN32)
    target_include_directories(MetodosNum2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
else()
    include_directories(deps/include)

    # Supressing warnings from raygui
    target_include_directories(MetodosNum2
        SYSTEM
        PRIVATE
        deps/include
    )
endif()