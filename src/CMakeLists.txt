file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(
    ${PROJECT_NAME}
    STATIC
        ${SOURCES}
        ${PROJECT_SOURCE_DIR}/deps/glad/src/gl.c
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(${PROJECT_NAME} PRIVATE ${CXX_FLAGS})

if(ENABLE_SANITIZERS)
    target_compile_options(${PROJECT_NAME} PUBLIC ${SANITIZER_FLAGS})
    target_link_options(${PROJECT_NAME} PUBLIC ${SANITIZER_FLAGS})
endif()

# MARK: - Dependencies

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/glad/include)

find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL)
