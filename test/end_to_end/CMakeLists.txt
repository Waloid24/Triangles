set(SOURCES main.cpp)

add_executable(end_to_end_tests ${SOURCES})

target_include_directories(end_to_end_tests 
                            PRIVATE ${INCLUDE_DIRECTORIES})