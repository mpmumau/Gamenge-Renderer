cmake_minimum_required(VERSION 3.10)

project(gamenge_renderer)

# Find GLEW
find_package(GLEW REQUIRED)

# Find OpenGL
find_package(GL REQUIRED)

# Find GLM
find_package(GLM REQUIRED)

# Find Assimp
find_package(assimp REQUIRED)

add_library(gamenge_renderer
    ${PROJECT_SOURCE_DIR}/src/renderer.cpp
    ${PROJECT_SOURCE_DIR}/src/renderable.cpp
    ${PROJECT_SOURCE_DIR}/src/shader_manager.cpp
    ${PROJECT_SOURCE_DIR}/src/texture_data.cpp
    ${PROJECT_SOURCE_DIR}/src/mesh_data.cpp
)

target_include_directories(gamenge_renderer
    ${PROJECT_SOURCE_DIR}/inc
)