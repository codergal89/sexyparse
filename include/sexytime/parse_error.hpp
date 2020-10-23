#ifndef SEXYTIME_PARSE_ERROR_HPP_
#define SEXYTIME_PARSE_ERROR_HPP_

#include <system_error>
#include <string>

namespace sexy
{
    enum struct parse_error
    {
        missing_expected_token = 1,
    };

    struct parse_error_category_impl final : std::error_category
    {
        char const *name() const noexcept override
        {
            return "SexyTime Parse Errors";
        }

        std::string message(int code) const override
        {
            switch (static_cast<parse_error>(code))
            {
            case parse_error::missing_expected_token:
                return "Missing expected token";
            default:
                return "Unknown parse error";
            }
        }
    };

    auto inline parse_error_category() -> std::error_category const &
    {
        auto static const category = parse_error_category_impl{};
        return category;
    }

    auto inline make_error_code(parse_error error) -> std::error_code
    {
        return {static_cast<int>(error), parse_error_category()};
    }

    auto inline make_error_condition(parse_error error) -> std::error_code
    {
        return {static_cast<int>(error), parse_error_category()};
    }

} // namespace sexy

namespace std
{
    template <>
    struct is_error_code_enum<sexy::parse_error> : true_type
    {
    };
} // namespace std

#endif