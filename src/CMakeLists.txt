set(TARGET fixlator)
set(TARGET_ROOT ${CMAKE_SOURCE_DIR}/src)

list(APPEND SOURCES
    PRIVATE
        FLApp.cpp
	    FLMain.cpp
        UserData.cpp
	    Printer.cpp
        ResultsListCtrl.cpp
        UserSettings.cpp
)

add_library(hffix INTERFACE)
target_include_directories(hffix INTERFACE ${hffix_SOURCE_DIR}/include)

message(STATUS "======== Configuring ${TARGET} ========")

if(APPLE)
    # Create bundle on Apple compilers
    add_executable(fixlator MACOSX_BUNDLE ${SRCS})

    # Set a custom plist file for the app bundle - needed for macOS retina display
    set_target_properties(fixlator PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist)
else()
    add_executable(fixlator WIN32 ${SRCS} ${CMAKE_SOURCE_DIR}/main.exe.manifest)
endif()

target_sources(${TARGET} PRIVATE ${SOURCES})
target_link_libraries(fixlator PRIVATE wxcore wxnet wxbase wxadv)
target_link_libraries(fixlator PUBLIC hffix)
