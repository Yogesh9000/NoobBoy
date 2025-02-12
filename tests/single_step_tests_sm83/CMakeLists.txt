find_package(nlohmann_json CONFIG REQUIRED)

add_executable(sst test_decoder_executor.cpp
                   ${PROJECT_SOURCE_DIR}/src/simple_bus.cpp
                   ${PROJECT_SOURCE_DIR}/src/decoder.cpp
                   ${PROJECT_SOURCE_DIR}/src/executor.cpp)
target_link_libraries(sst PRIVATE GTest::gtest GTest::gtest_main
                                  nlohmann_json::nlohmann_json)

include(GoogleTest)
gtest_discover_tests(sst WORKING_DIRECTORY
                         ${PROJECT_SOURCE_DIR}/tests/single_step_tests_sm83)
