# Project Instructions

## Exceptions

- Do not use C++ exceptions. Use `goon::core::panic` instead.

## Assertions

- Use `goon::core::assert_that`, `goon::core::assert_eq`, and `goon::core::assert_ne` from `core/assert.hpp` instead of the C/C++ `assert` macro.
- Use `assert_eq` and `assert_ne` for equality comparisons so failures report both operand values; use `assert_that` for other boolean conditions.
