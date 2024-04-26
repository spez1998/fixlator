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

add_subdirectory("src")
