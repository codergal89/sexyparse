#include "sexyparse/maybe.hpp"

#include "catch2/catch.hpp"

#include <string>
#include <system_error>

using namespace std::string_literals;

TEST_CASE("A 'maybe' can be constructed with a value")
{
    sexy::maybe{"Test Value"s};
}

TEST_CASE("A 'maybe' can be constructed with a constant value")
{
    auto const value = "Constant Value"s;
    sexy::maybe{value};
}

TEST_CASE("A 'maybe<bool>' can be checked by bool conversion")
{
    REQUIRE(static_cast<bool>(sexy::maybe{false}));
}

TEST_CASE("A 'maybe' can be constructed with an error code")
{
    sexy::maybe<long>{make_error_code(std::errc::no_lock_available)};
}

TEST_CASE("A 'maybe' constructed with a value converts to true")
{
    REQUIRE(static_cast<bool>(sexy::maybe{42}));
}

TEST_CASE("A 'maybe' constructed with an error converts to false")
{
    REQUIRE(!static_cast<bool>(sexy::maybe<float>{make_error_code(std::errc::invalid_argument)}));
}

TEST_CASE("A 'maybe' constructed with a value converts to the same value")
{
    REQUIRE(static_cast<double>(sexy::maybe{1337.0}) == 1337.0);
}

TEST_CASE("Trying to convert a 'maybe' constructed with an error throws sexy::bad_maybe_access")
{
    REQUIRE_THROWS_AS(static_cast<char>(sexy::maybe<char>{make_error_code(std::errc::io_error)}), sexy::bad_maybe_access);
}

TEST_CASE("A 'maybe' constructed with an error converts to the same error")
{
    REQUIRE(static_cast<std::error_code>(sexy::maybe<unsigned>{make_error_code(std::errc::no_link)}) == std::errc::no_link);
}

TEST_CASE("Converting a 'maybe' constructed with a value yields the empty error code")
{
    REQUIRE(static_cast<std::error_code>(sexy::maybe{10ull}) == std::error_code{});
}

TEST_CASE("Mapping over a 'maybe' constructed with a value calls the supplied function")
{
    auto did_call_function{false};
    sexy::maybe{42}.map([&](auto value) { did_call_function = true; return value; });
    REQUIRE(did_call_function);
}

TEST_CASE("Mapping over a 'maybe' constructed with a value yields the supplied function's result in a new maybe")
{
    auto result = sexy::maybe{'c'}.map([](auto) { return 42; });
    REQUIRE(static_cast<int>(result) == 42);
}

TEST_CASE("Mapping over a 'maybe' constructed with an error does not call the supplied function")
{
    auto did_call_function{false};
    sexy::maybe<wchar_t>{make_error_code(std::errc::address_family_not_supported)}.map([&](auto value) { did_call_function = true; return value; });
    REQUIRE(!did_call_function);
}

TEST_CASE("Mapping over a 'maybe' constructed with an error yield a maybe with the same error")
{
    auto result = sexy::maybe<int>{make_error_code(std::errc::argument_out_of_domain)}.map([](auto value) { return value; });
    REQUIRE(static_cast<std::error_code>(result) == std::errc::argument_out_of_domain);
}