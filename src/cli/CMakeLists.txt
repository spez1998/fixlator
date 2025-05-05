set(TARGET_CLI fixlator_cli)
list(APPEND SOURCES_CLI
    FLMain.cpp
)

add_executable(${TARGET_CLI} ${SOURCES_CLI})

target_include_directories(${TARGET_CLI} PRIVATE 
    ${hffix_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(${TARGET_CLI} PRIVATE hffix FixlatorBase)
