#include "sexyparse/maybe.hpp"

#include "catch2/catch.hpp"

#include <string>
#include <system_error>
#include <utility>

using namespace std::string_literals;

TEST_CASE("A 'maybe' constructed with a value converts to the same value")
{
    REQUIRE(static_cast<double>(sexy::maybe{1337.0}) == 1337.0);
}

TEST_CASE("Trying to convert a 'maybe' constructed with an error throws sexy::bad_maybe_access")
{
    REQUIRE_THROWS_AS(static_cast<char>(sexy::maybe<char>{make_error_code(std::errc::io_error)}), sexy::bad_maybe_access);
}
