#include "catch2/catch.hpp"
#include<list>
#include "lob.hpp"

// Used to test Catch2 itself is working instead of bad linking
// TEST_CASE("simple test", "[classic]") {
//     std::cout << "simple test";
//     REQUIRE(1 == 1);
// }

TEST_CASE("test limit implementation", "[limit]") {
    // initialize limit object
    Limit baseLimit = Limit(0, 1);
    Limit helperLimit = Limit(1, 1);
    Order helperOrder = Order(1, true, 5, 0);

    SECTION("check initialization") {
        // check intialization of member variables
        REQUIRE(baseLimit.limitPrice == 0);
        REQUIRE(baseLimit.size == 1);

        // check initialization of pointers
        REQUIRE_FALSE(baseLimit.getParent());
        REQUIRE_FALSE(baseLimit.getLeftChild());
        REQUIRE_FALSE(baseLimit.getRightChild());
        REQUIRE_FALSE(baseLimit.getHeadOrder());
        REQUIRE_FALSE(baseLimit.getTailOrder());
    }

    SECTION("check instance variable setting") {
        baseLimit.setParent(&helperLimit);
        REQUIRE(baseLimit.getParent() == &helperLimit);

        baseLimit.setLeftChild(&helperLimit);
        REQUIRE(baseLimit.getLeftChild() == &helperLimit);

        baseLimit.setRightChild(&helperLimit);
        REQUIRE(baseLimit.getRightChild() == &helperLimit);

        baseLimit.setHeadOrder(&helperOrder);
        REQUIRE(baseLimit.getHeadOrder() == &helperOrder);

        baseLimit.setTailOrder(&helperOrder);
        REQUIRE(baseLimit.getTailOrder() == &helperOrder);
    }

    SECTION("check comparator functions on limits") {
        std::vector<Limit*> limitVector = {&helperLimit, &baseLimit};

        // sort in ascending order
        std::sort(limitVector.begin(), limitVector.end(), LimitLesser());
        REQUIRE(limitVector[0] == &baseLimit);
        REQUIRE(limitVector[1] == &helperLimit);

        // sort in descending order
        std::sort(limitVector.begin(), limitVector.end(), LimitGreater());
        REQUIRE(limitVector[0] == &helperLimit);
        REQUIRE(limitVector[1] == &baseLimit);
    }
}

