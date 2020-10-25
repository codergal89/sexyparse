#include "sexyparse/maybe.hpp"

#include "catch2/catch.hpp"

#include <string>
#include <system_error>
#include <utility>

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

TEST_CASE("A 'maybe' can be constructed with an error code")
{
    sexy::maybe<long>{make_error_code(std::errc::no_lock_available)};
}
