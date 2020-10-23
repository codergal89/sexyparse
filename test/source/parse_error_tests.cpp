#include "sexytime/parse_error.hpp"

#include "catch2/catch.hpp"

#include <string>

using namespace std::string_literals;

TEST_CASE("Out-of-range int for parse_error_category::message produces \"Unknown parse error\"")
{
    REQUIRE(sexy::parse_error_category().message(-1) == "Unknown parse error");
}

TEST_CASE("1 for parse_error_category::message produces \"Missing expected token\"")
{
    REQUIRE(sexy::parse_error_category().message(1) == "Missing expected token");
}

TEST_CASE("parse_error_category::name is \"SexyTime Parse Errors\"")
{
    REQUIRE(sexy::parse_error_category().name() == "SexyTime Parse Errors"s);
}

TEST_CASE("make_error_code with sexy::parse_error associates the code with the parse_error_category")
{
    REQUIRE(make_error_code(sexy::parse_error::missing_expected_token).category() == sexy::parse_error_category());
}

TEST_CASE("make_error_condition with sexy::parse_error associates the condition with the parse_error_category")
{
    REQUIRE(make_error_condition(sexy::parse_error::missing_expected_token).category() == sexy::parse_error_category());
}