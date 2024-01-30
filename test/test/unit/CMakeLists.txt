set(SOURCES triangle.cpp)

include(GoogleTest)

add_executable(unit_tests ${SOURCES})

target_link_libraries(unit_tests
                      PRIVATE ${GTEST_LIBRARIES}
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                      PRIVATE m)

target_include_directories(unit_tests
                            PRIVATE ${INCLUDE_DIRECTORIES})

gtest_discover_tests(unit_tests)