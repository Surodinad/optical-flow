cmake_minimum_required(VERSION 3.10)
project(lk)

add_subdirectory(../jpg ImgLibBuildDir)

add_executable(lk main.cpp one_dimensional/one_dimensional.cpp one_dimensional/fiction.cpp)
target_include_directories(lk PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../jpg")
target_link_libraries(lk ImgLib ${SYSTEM_LIBS})
