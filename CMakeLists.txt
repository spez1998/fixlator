cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(
    fixlator
    VERSION 1.0
    DESCRIPTION "A fast and lightweight FIX parser and translator"
    LANGUAGES CXX
)

include(FetchContent)
include(CMakePrintHelpers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(wxBUILD_SHARED OFF)

message(STATUS "Fetching wxWidgets...")
FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY https://github.com/wxwidgets/wxWidgets.git
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(wxWidgets)

message(STATUS "Fetching hffix...")
FetchContent_Declare(
    hffix
    GIT_REPOSITORY https://github.com/jamesdbrock/hffix.git
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(hffix)

message(STATUS "Fetching date...")
FetchContent_Declare(
    date
    GIT_REPOSITORY https://github.com/HowardHinnant/date
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(date)

message(STATUS "Fetching googletest...")
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG main
    GIT_SHALLOW ON
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(hffix INTERFACE)

add_subdirectory("src/base")
add_subdirectory("src/cli")
add_subdirectory("src/gui")
add_subdirectory("test/base")
