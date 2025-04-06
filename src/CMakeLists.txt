set(TARGET_ROOT ${CMAKE_SOURCE_DIR}/src)
set(TARGET_GUI fixlator_gui)
set(TARGET_CLI fixlator)

list(APPEND SOURCES_GUI
        gui/FLApp.cpp
        gui/FLMain.cpp
        gui/ResultsListCtrl.cpp
        gui/UserSettings.cpp

        base/UserData.cpp
        base/Printer.cpp
)

list(APPEND SOURCES_CLI
        cli/FLMain.cpp

        base/UserData.cpp
        base/Printer.cpp
)


# I'm pretty sure hffix deals with including date/date.h
add_library(hffix INTERFACE)
target_include_directories(hffix INTERFACE ${hffix_SOURCE_DIR}/include)

message(STATUS "======== Configuring ${TARGET_GUI} ========")
message(${CMAKE_SOURCE_DIR})

if(APPLE)
    # Create bundle on Apple compilers
    add_executable(${TARGET_GUI} MACOSX_BUNDLE ${SRCS})

    # Set a custom plist file for the app bundle - needed for macOS retina display
    set_target_properties(${TARGET_GUI} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist)
else()
    add_executable(${TARGET_GUI} WIN32 ${SOURCES_GUI} ${CMAKE_SOURCE_DIR}/main.exe.manifest)
endif()

include_directories(${TARGET_ROOT})

target_sources(${TARGET_GUI} PRIVATE ${SOURCES_GUI})
target_link_libraries(${TARGET_GUI} PRIVATE wxcore wxnet wxbase wxadv)
target_link_libraries(${TARGET_GUI} PUBLIC date hffix)

add_executable(${TARGET_CLI} ${SOURCES_CLI})
target_sources(${TARGET_CLI} PRIVATE ${SOURCES_CLI})
target_link_libraries(${TARGET_CLI} PUBLIC hffix)
