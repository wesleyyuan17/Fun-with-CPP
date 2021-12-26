#include "catch2/catch.hpp"
#include<iostream>
#include "lob.hpp"

TEST_CASE("simple test", "[classic]") {
    std::cout << "simple test";
    REQUIRE(1 == 1);
}

TEST_CASE("first test", "[limit]") {
    Limit l = Limit(0, 1);
    REQUIRE(l.limitPrice == 0);
}

