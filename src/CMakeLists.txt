file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

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

# Boost
find_package(Boost REQUIRED COMPONENTS hana)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::hana)

# glad
add_library(glad STATIC ${PROJECT_SOURCE_DIR}/deps/glad/src/gl.c)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/deps/glad/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

# glfw
find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# plf_hive
add_library(plf_hive INTERFACE)
target_include_directories(plf_hive INTERFACE ${PROJECT_SOURCE_DIR}/deps/plf_hive/include)
target_link_libraries(${PROJECT_NAME} PUBLIC plf_hive)

# stb
add_library(stb STATIC ${PROJECT_SOURCE_DIR}/deps/stb/src/stb_image.c)
target_include_directories(stb PUBLIC ${PROJECT_SOURCE_DIR}/deps/stb/include)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)
