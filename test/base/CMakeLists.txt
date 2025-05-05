enable_testing()

add_executable(TestUserData TestUserData.cpp)
target_include_directories(TestUserData PRIVATE ${hffix_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR})
target_link_libraries(TestUserData GTest::gtest_main FixlatorBase)

include(GoogleTest)
gtest_discover_tests(TestUserData)
