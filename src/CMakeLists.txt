set(TARGET fixlator_gui)
set(TARGET_ROOT ${CMAKE_SOURCE_DIR}/src)

list(APPEND SOURCES
    PRIVATE
        gui/FLApp.cpp
        gui/FLMain.cpp
        gui/ResultsListCtrl.cpp
        gui/UserSettings.cpp

        base/UserData.cpp
        base/Printer.cpp
)

# I'm pretty sure hffix deals with including date/date.h
add_library(hffix INTERFACE)
target_include_directories(hffix INTERFACE ${hffix_SOURCE_DIR}/include)

message(STATUS "======== Configuring ${TARGET} ========")

if(APPLE)
    # Create bundle on Apple compilers
    add_executable(${TARGET} MACOSX_BUNDLE ${SRCS})

    # Set a custom plist file for the app bundle - needed for macOS retina display
    set_target_properties(${TARGET} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist)
else()
	add_executable(${TARGET} WIN32 ${SRCS} ${CMAKE_SOURCE_DIR}/main.exe.manifest)
endif()

include_directories(${TARGET_ROOT})

target_sources(${TARGET} PRIVATE ${SOURCES})
target_link_libraries(${TARGET} PRIVATE wxcore wxnet wxbase wxadv)
target_link_libraries(${TARGET} PUBLIC date hffix)
