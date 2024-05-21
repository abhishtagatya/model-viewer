cmake_minimum_required(VERSION 3.27)
project(model_viewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(GLFW3 REQUIRED)

if (APPLE)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(OPENGL_FRAMEWORK OpenGL)
    find_library(IOKIT_FRAMEWORK IOKit)
endif()

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(model_viewer ${SOURCES})

if (APPLE)
    target_link_libraries(${PROJECT_NAME} ${COCOA_FRAMEWORK} ${OPENGL_FRAMEWORK} ${IOKIT_FRAMEWORK} glfw)
endif()