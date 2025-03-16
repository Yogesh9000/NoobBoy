set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

add_executable(gb main.cpp gb.cpp cpu.cpp executor.cpp simple_bus.cpp timer.cpp)
