list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

configure_file(${CMAKE_SOURCE_DIR}/cmake/GoogleTest-CMakeLists.txt.in 
    ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt
)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download
)

if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download
)

if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
    ${CMAKE_BINARY_DIR}/googletest-build
    EXCLUDE_FROM_ALL
)

add_executable(renderer_test
    src/camera_test.cpp
    src/texture_data_test.cpp
    src/mesh_data_test.cpp
    src/shader_data_test.cpp
    src/renderer_test.cpp
    src/main_test.cpp
)

# target_compile_features(renderer_test PRIVATE cxx_auto_type)

target_link_libraries(renderer_test 
    gmock_main 
    gtest_main
    OpenGL::GL
    ${GLEW_LIBRARIES}
    ${ASSIMP_LIBRARIES}
    Gamenge::Renderer
)

target_include_directories(renderer_test
    PUBLIC
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${ASSIMP_INCLUDE_DIRS}
)

add_test(NAME renderer_test COMMAND renderer_test)