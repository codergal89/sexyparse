#ifndef SEXYPARSE_MAYBE_HPP_
#define SEXYPARSE_MAYBE_HPP_

#include <variant>
#include <system_error>
#include <type_traits>
#include <utility>
#include <functional>

namespace sexy
{

    namespace internal
    {
        struct maybe_error_tag
        {
        };

        struct maybe_value_tag
        {
        };
    } // namespace internal

    using bad_maybe_access = std::bad_variant_access;

    template <typename ValueType>
    struct maybe
    {
        using value_type = ValueType;
        using error_type = std::error_code;

        constexpr explicit maybe(ValueType const &value) : m_underlying{value}
        {
        }

        constexpr explicit maybe(ValueType &&value) : m_underlying{std::move(value)}
        {
        }

        explicit maybe(std::error_code error) : m_underlying{std::move(error)}
        {
        }

        constexpr operator bool() const noexcept
        {
            return std::holds_alternative<value_type>(m_underlying);
        }

        template <typename Enabler = ValueType, typename = std::enable_if_t<!std::is_same_v<std::decay_t<Enabler>, bool>>>
        constexpr explicit operator value_type() const
        {
            return std::get<value_type>(m_underlying);
        }

        explicit operator error_type() const noexcept
        {
            if (std::holds_alternative<error_type>(m_underlying))
            {
                return std::get<error_type>(m_underlying);
            }
            return std::error_code{};
        }

        template <typename Callable>
        auto constexpr map(Callable &&callable) -> std::enable_if_t<std::is_invocable_v<Callable, value_type>,
                                                                    maybe<std::invoke_result_t<Callable, value_type>>>
        {
            using result_type = std::invoke_result_t<Callable, value_type>;
            if (*this)
            {
                return maybe<result_type>{std::invoke(std::forward<Callable>(callable), std::get<value_type>(m_underlying))};
            }
            return maybe<result_type>{std::get<error_type>(m_underlying)};
        }

    private:
        std::variant<value_type, error_type> m_underlying;
    };

} // namespace sexy

#endif