cmake_minimum_required(VERSION 3.0.0)

project(HelloGL)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory("external/SDL")
add_subdirectory("external/glew/build/cmake")

set(SOURCE_FILES "src/main.cpp")
add_executable(HelloGL ${SOURCE_FILES})

target_include_directories(HelloGL PUBLIC "${CMAKE_CURRENT_LIST_DIR}/external/SDL/include")
target_link_libraries(HelloGL PUBLIC SDL3::SDL3-shared)

target_include_directories(HelloGL PUBLIC "${CMAKE_CURRENT_LIST_DIR}/external/glew/include")
target_link_libraries(HelloGL PUBLIC glew_s)
