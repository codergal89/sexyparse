#include "sexyparse/maybe.hpp"

#include "catch2/catch.hpp"

#include <string>
#include <system_error>
#include <utility>

using namespace std::string_literals;

TEST_CASE("A 'maybe' constructed with a value converts to true")
{
    REQUIRE(static_cast<bool>(sexy::maybe{42}));
}

TEST_CASE("A 'maybe<bool>' can be checked by bool conversion")
{
    REQUIRE(static_cast<bool>(sexy::maybe{false}));
}

TEST_CASE("A 'maybe' constructed with an error converts to false")
{
    REQUIRE(!static_cast<bool>(sexy::maybe<float>{make_error_code(std::errc::invalid_argument)}));
}
