find_package(nlohmann_json CONFIG REQUIRED)

add_executable(test_load test_load_instruction.cpp
                   ${PROJECT_SOURCE_DIR}/src/simple_bus.cpp
                   ${PROJECT_SOURCE_DIR}/src/executor.cpp)
target_link_libraries(test_load PRIVATE GTest::gtest GTest::gtest_main
                                  nlohmann_json::nlohmann_json)

add_executable(test_special test_special_instruction.cpp
                   ${PROJECT_SOURCE_DIR}/src/simple_bus.cpp
                   ${PROJECT_SOURCE_DIR}/src/executor.cpp)
target_link_libraries(test_special PRIVATE GTest::gtest GTest::gtest_main
                                  nlohmann_json::nlohmann_json)

add_executable(test_arithmetic test_arithmetic_instruction.cpp
                   ${PROJECT_SOURCE_DIR}/src/simple_bus.cpp
                   ${PROJECT_SOURCE_DIR}/src/executor.cpp)
target_link_libraries(test_arithmetic PRIVATE GTest::gtest GTest::gtest_main
                                  nlohmann_json::nlohmann_json)

add_executable(test_flow test_control_flow_instruction.cpp
                   ${PROJECT_SOURCE_DIR}/src/simple_bus.cpp
                   ${PROJECT_SOURCE_DIR}/src/executor.cpp)
target_link_libraries(test_flow PRIVATE GTest::gtest GTest::gtest_main
                                  nlohmann_json::nlohmann_json)

add_executable(test_rs test_rotate_shift_instruction.cpp
                   ${PROJECT_SOURCE_DIR}/src/simple_bus.cpp
                   ${PROJECT_SOURCE_DIR}/src/executor.cpp)
target_link_libraries(test_rs PRIVATE GTest::gtest GTest::gtest_main
                                  nlohmann_json::nlohmann_json)

include(GoogleTest)
gtest_discover_tests(test_load WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests/single_step_tests_sm83)
gtest_discover_tests(test_special WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests/single_step_tests_sm83)
gtest_discover_tests(test_arithmetic WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests/single_step_tests_sm83)
gtest_discover_tests(test_flow WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests/single_step_tests_sm83)
gtest_discover_tests(test_rs WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests/single_step_tests_sm83)
