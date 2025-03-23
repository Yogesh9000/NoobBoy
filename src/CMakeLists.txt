set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

find_package(SDL3 CONFIG REQUIRED)

add_executable(gb main.cpp gb.cpp cpu.cpp executor.cpp simple_bus.cpp timer.cpp ppu.cpp)
target_link_libraries(gb PRIVATE SDL3::SDL3)
