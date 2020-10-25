#include "sexyparse/maybe.hpp"

#include "catch2/catch.hpp"

#include <string>
#include <system_error>
#include <utility>

using namespace std::string_literals;

TEST_CASE("unwrap can retrieve the value from a constant lvalue 'maybe'")
{
    auto const object = sexy::maybe{42};
    REQUIRE(object.unwrap() == 42);
}

TEST_CASE("unwrap can retrieve the value from a mutable lvalue 'maybe'")
{
    auto object = sexy::maybe{42};
    REQUIRE(object.unwrap() == 42);
}

TEST_CASE("unwrap can retrieve the value from a constant xvalue 'maybe'")
{
    auto const object = sexy::maybe{42};
    REQUIRE(std::move(object).unwrap() == 42);
}

TEST_CASE("unwrap can retrieve the value from a mutable xvalue 'maybe'")
{
    REQUIRE(sexy::maybe{42}.unwrap() == 42);
}

TEST_CASE("Trying to unwrap a constant 'maybe' lvalue constructed with an error throws sexy::bad_maybe_access")
{
    auto const object = sexy::maybe<int>{make_error_code(std::errc::device_or_resource_busy)};
    REQUIRE_THROWS_AS(object.unwrap(), sexy::bad_maybe_access);
}

TEST_CASE("Trying to unwrap a mutable 'maybe' lvalue constructed with an error throws sexy::bad_maybe_access")
{
    auto object = sexy::maybe<int>{make_error_code(std::errc::device_or_resource_busy)};
    REQUIRE_THROWS_AS(object.unwrap(), sexy::bad_maybe_access);
}

TEST_CASE("Trying to unwrap a constant 'maybe' xvalue constructed with an error throws sexy::bad_maybe_access")
{
    auto const object = sexy::maybe<int>{make_error_code(std::errc::device_or_resource_busy)};
    REQUIRE_THROWS_AS(std::move(object).unwrap(), sexy::bad_maybe_access);
}

TEST_CASE("Trying to unwrap a mutable 'maybe' xvalue constructed with an error throws sexy::bad_maybe_access")
{
    REQUIRE_THROWS_AS(sexy::maybe<int>{make_error_code(std::errc::device_or_resource_busy)}.unwrap(), sexy::bad_maybe_access);
}