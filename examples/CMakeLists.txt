add_executable(basic basic.cpp)

target_link_libraries(
    basic
    PRIVATE
        ${PROJECT_NAME}
)

target_compile_options(basic PRIVATE ${CXX_FLAGS})
