cmake_minimum_required(VERSION 3.10)

project(gamenge_renderer VERSION 0.1.0 LANGUAGES CXX)

find_package(GLEW REQUIRED)
find_package(GL REQUIRED)
find_package(GLM REQUIRED)
find_package(assimp REQUIRED)

add_library(gamenge_renderer
    ${PROJECT_SOURCE_DIR}/source/src/camera.cpp
    ${PROJECT_SOURCE_DIR}/source/src/mesh_data.cpp
    ${PROJECT_SOURCE_DIR}/source/src/renderable.cpp
    ${PROJECT_SOURCE_DIR}/source/src/renderer.cpp
    ${PROJECT_SOURCE_DIR}/source/src/shader_manager.cpp
    ${PROJECT_SOURCE_DIR}/source/src/texture_data.cpp
)

target_include_directories(gamenge_renderer
    ${PROJECT_SOURCE_DIR}/source/inc
)