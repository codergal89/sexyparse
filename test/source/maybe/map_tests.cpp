#include "sexyparse/maybe.hpp"

#include "catch2/catch.hpp"

#include <string>
#include <system_error>
#include <utility>

using namespace std::string_literals;

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

TEST_CASE("Can map over a constant 'maybe' instance")
{
    auto const object = sexy::maybe{"Hello, World!\n"s};
    object.map([](auto const &) { return true; });
}