#pragma once

#include <utility>

namespace goon::core {

template<typename Fn> class ScopeExit final {
  public:
    constexpr explicit ScopeExit(Fn function) noexcept
        : function{std::move(function)} {}

    ScopeExit(const ScopeExit&) = delete;
    ScopeExit(ScopeExit&&) = delete;

    constexpr ~ScopeExit() noexcept {
        this->function();
    }

    auto operator=(const ScopeExit&) -> ScopeExit& = delete;
    auto operator=(ScopeExit&&) -> ScopeExit& = delete;

  private:
    Fn function;
};

namespace detail {

struct Defer final {};

template<typename Fn>
[[nodiscard]]
// NOLINTNEXTLINE(fuchsia-overloaded-operator, readability-named-parameter)
constexpr auto operator+(const Defer, Fn function) noexcept -> ScopeExit<Fn> {
    return ScopeExit<Fn>{std::move(function)};
}

} // namespace detail

} // namespace goon::core

// NOLINTBEGIN(cppcoreguidelines-macro-usage, readability-identifier-naming)

#define GOON_DETAIL_CONCAT_IMPL(left, right) left##right
#define GOON_DETAIL_CONCAT(left, right) GOON_DETAIL_CONCAT_IMPL(left, right)

//
// Usage:
//
// defer({
//     ...
// });
//
#define defer(...)                                                             \
    [[maybe_unused]] const auto GOON_DETAIL_CONCAT(                            \
        goon_deferred_action_, __COUNTER__                                     \
    ) {                                                                        \
        ::goon::core::detail::Defer{} + [&]() noexcept -> void __VA_ARGS__     \
    }

// NOLINTEND(cppcoreguidelines-macro-usage, readability-identifier-naming)
