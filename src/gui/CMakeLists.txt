set(TARGET_GUI fixlator_gui)
list(APPEND SOURCES_GUI
    FLApp.cpp
    FLMain.cpp
    ResultsListCtrl.cpp
    UserSettings.cpp
)

if(APPLE)
    # Create bundle on Apple compilers
    add_executable(${TARGET_GUI} MACOSX_BUNDLE ${SOURCES_GUI})

    # Set a custom plist file for the app bundle - needed for macOS retina display
    set_target_properties(${TARGET_GUI} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist)
else()
    add_executable(${TARGET_GUI} WIN32 ${SOURCES_GUI} ${CMAKE_SOURCE_DIR}/main.exe.manifest)
endif()

target_sources(${TARGET_GUI} PRIVATE ${SOURCES_GUI})
target_include_directories(${TARGET_GUI} PRIVATE ${hffix_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${TARGET_GUI} PRIVATE date hffix FixlatorBase wxcore wxnet wxbase wxadv)
