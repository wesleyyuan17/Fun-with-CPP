#include "catch2/catch.hpp"
#include "lob.hpp"

TEST_CASE("test order implementation", "[order]") {
    // initialize limit object
    Order baseOrder = Order(1, true, 5, 0);
    Order helperOrder = Order(2, true, 3, 0);
    Limit helperLimit = Limit(0, 1);

    SECTION("check initialization") {
        // check intialization of member variables
        REQUIRE(baseOrder.idNumber == 1);
        REQUIRE(baseOrder.buyOrSell);
        REQUIRE(baseOrder.shares == 5);
        REQUIRE(baseOrder.limit == 0);

        // check initialization of pointers
        REQUIRE(baseOrder.getEntryTime() == -1);
        REQUIRE(baseOrder.getEventTime() == -1);
        REQUIRE_FALSE(baseOrder.getNextOrder());
        REQUIRE_FALSE(baseOrder.getPrevOrder());
        REQUIRE_FALSE(baseOrder.getParentLimit());
    }

    SECTION("check instance variable setting") {
        baseOrder.setEntryTime(1);
        REQUIRE(baseOrder.getEntryTime() == 1);
        
        baseOrder.setEventTime(1);
        REQUIRE(baseOrder.getEventTime() == 1);

        baseOrder.setNextOrder(&helperOrder);
        REQUIRE(baseOrder.getNextOrder() == &helperOrder);
        
        baseOrder.setPrevOrder(&helperOrder);
        REQUIRE(baseOrder.getPrevOrder() == &helperOrder);

        baseOrder.setParentLimit(&helperLimit);
        REQUIRE(baseOrder.getParentLimit() == &helperLimit);
    }
}