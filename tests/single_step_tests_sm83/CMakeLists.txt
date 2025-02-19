find_package(nlohmann_json CONFIG REQUIRED)

add_executable(test_load test_load_instruction.cpp
                   ${PROJECT_SOURCE_DIR}/src/simple_bus.cpp
                   ${PROJECT_SOURCE_DIR}/src/executor.cpp)
target_link_libraries(test_load PRIVATE GTest::gtest GTest::gtest_main
                                  nlohmann_json::nlohmann_json)

include(GoogleTest)
gtest_discover_tests(test_load WORKING_DIRECTORY
                         ${PROJECT_SOURCE_DIR}/tests/single_step_tests_sm83)
