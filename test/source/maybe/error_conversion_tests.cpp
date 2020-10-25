#include "sexyparse/maybe.hpp"

#include "catch2/catch.hpp"

#include <string>
#include <system_error>
#include <utility>

using namespace std::string_literals;

TEST_CASE("A 'maybe' constructed with an error converts to the same error")
{
    REQUIRE(static_cast<std::error_code>(sexy::maybe<unsigned>{make_error_code(std::errc::no_link)}) == std::errc::no_link);
}

TEST_CASE("Converting a 'maybe' constructed with a value yields the empty error code")
{
    REQUIRE(static_cast<std::error_code>(sexy::maybe{10ull}) == std::error_code{});
}
