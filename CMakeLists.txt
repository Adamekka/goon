cmake_minimum_required(VERSION 3.28)

# MARK: Project

project(goon LANGUAGES C CXX)

# MARK: Tooling

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" ON)

# MARK: Warnings

set(CXX_FLAGS
    -Wall
    -Wcast-align
    -Wextra
    -Wformat
    -Wformat-security
    -Wno-shadow
    -Wno-unused-result
    -Wnull-dereference
    -Wredundant-decls
    -Wreturn-type
    -Wstrict-overflow
    -Wuninitialized
    -Wvla
    -fstack-protector-strong
)

set(SANITIZER_FLAGS
    -fsanitize=address
    -fsanitize=undefined
)

# MARK: Target

add_subdirectory(src)
add_subdirectory(examples)
