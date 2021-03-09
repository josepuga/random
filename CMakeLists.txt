cmake_minimum_required(VERSION 3.0.0)
project(random VERSION 
    1.0.0
    DESCRIPTION "Random number generator class. Using C++ Mersenne twister."
)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17 CACHE STRING "")
endif()

if(CMAKE_CXX_STANDARD LESS 17)
    message(FATAL_ERROR " C++ incompatible standard ${CMAKE_CXX_STANDARD}. Required C++17")
endif()

#Compiler options
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /permissive-")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
endif()

#OS options
option(MINGW_STATIC_LINK "Link MinGW dependencies statically." ON)
option(MSVC_STATIC_LINK "Link MSVC static C++ runtime library." OFF)
if(WIN32)
    message("Windows OS detected.")
    if(MSVC AND MSVC_STATIC_LINK)
        message("Linking MSVC C++ runtime statically...")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD /MT")
    endif()
    if(NOT MSVC AND MINGW_STATIC_LINK)
        message("Linking MinGW dependencies statically...")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static -pthread")
        endif()
endif()

add_executable(test_random
    test/test_random.cpp
)

include_directories(src)

#Build type options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Building Debug...")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Building Release...") 
endif()



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
