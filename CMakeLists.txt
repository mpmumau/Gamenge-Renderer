cmake_minimum_required(VERSION 3.10)

project(renderer VERSION 0.1.0 LANGUAGES CXX)

find_package(GL REQUIRED)
find_package(GLU REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

add_library(renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/mesh_data.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/renderable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/shader_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/texture_data.cpp
)

add_library(Gamenge::Renderer ALIAS renderer)

target_include_directories(gamenge_renderer
    PUBLIC:
        $<INSTALL_INTERFACE:source/inc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/inc>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source/src
)

target_compile_options(renderer 
    PRIVATE 
        $<$<CXX_COMPILER_ID:GNU>:-Wall>
)

target_link_libraries(renderer
    PUBLIC
        GL::GL
        GLU::GLU
        GLEW::GLEW
        assimp::assimp
    PRIVATE
        # Boost::???
)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/Renderer)

install(TARGETS renderer
    EXPORT renderer-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(renderer PROPERTIES EXPORT_NAME Renderer)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT renderer-targets
    FILE
        RendererTargets.cmake
    NAMESPACE
        Gamenge::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/RendererConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/RendererConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/RendererConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/RendererConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/RendererConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT renderer-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/RendererTargets.cmake
    NAMESPACE Gamenge::
)

export(PACKAGE Renderer)

#add_subdirectory(test)
