cmake_minimum_required(VERSION 3.10)

set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   1   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

project(renderer VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} LANGUAGES CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

add_library(renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/mesh_data.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/renderable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/shader_data.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/texture_data.cpp
)

add_library(Gamenge::Renderer ALIAS renderer)

target_include_directories(renderer
    PUBLIC
        $<INSTALL_INTERFACE:source/inc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/inc>
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source/src
        ${ASSIMP_INCLUDE_DIRS}
)

target_compile_options(renderer
    PRIVATE 
        $<$<CXX_COMPILER_ID:GNU>:-Wall>
)

target_link_libraries(renderer
    PUBLIC
        OpenGL::GL
        ${GLEW_LIBRARIES}
        ${ASSIMP_LIBRARIES}
    PRIVATE
        # Boost::???
)

include(GNUInstallDirs)
set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}/gamenge/renderer")

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/Renderer)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

install(TARGETS renderer
    EXPORT renderer-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(renderer PROPERTIES EXPORT_NAME Renderer)

install(DIRECTORY source/inc/gamenge DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

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

find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})
if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/html DESTINATION share/doc/gamenge/renderer)
endif()

enable_testing()
add_subdirectory(test)


