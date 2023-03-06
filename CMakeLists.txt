cmake_minimum_required (VERSION 3.15)
project (tinyraytracer)

find_package(PNGPP REQUIRED)


add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} pngpp::pngpp)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)