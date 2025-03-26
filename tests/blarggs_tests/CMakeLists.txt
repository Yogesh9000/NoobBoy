find_package(nlohmann_json CONFIG REQUIRED)

add_executable(test_cpu_individual test_cpu_individual_instruction.cpp
                   dummy_bus.cpp
                   ${PROJECT_SOURCE_DIR}/src/executor.cpp
                   ${PROJECT_SOURCE_DIR}/src/cpu.cpp
                   ${PROJECT_SOURCE_DIR}/src/simple_bus.cpp
                   ${PROJECT_SOURCE_DIR}/src/timer.cpp)
target_link_libraries(test_cpu_individual
                      PRIVATE GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_cpu_individual
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests/blarggs_tests)
