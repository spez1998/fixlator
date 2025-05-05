add_library(FixlatorBase OBJECT UserData.cpp Controller.cpp Printer.cpp)

target_include_directories(FixlatorBase PRIVATE ${hffix_SOURCE_DIR}/include)
target_link_libraries(FixlatorBase PRIVATE hffix)
