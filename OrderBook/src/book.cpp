#pragma once
#include<assert.h>
#include<queue>
#include<map>
#include "lob.hpp"

Book::Book() {
    // set pointers to be null for now
    this->buyHeap = std::priority_queue<Limit*, std::vector<Limit*>, LimitLesser>();
    this->sellHeap = std::priority_queue<Limit*, std::vector<Limit*>, LimitGreater>();
    this->openOrders = std::map<int, Order*>();
    this->availableLimits = std::map<int, Limit*>();

    // book is empty, inside of book set to null pointers
    this->highestBuy = nullptr;
    this->lowestSell = nullptr;
}

/*
Assumes some other system is in place for taking in orders, creating order objects w/ idNumbers, etc.
*/

void Book::add(Order* order) {
    // execute if limit price is at market
    if (order->buyOrSell && order->limit >= this->highestBuy->limitPrice) {
        // liquidity taking buy order - walk the sell book
        this->executeBuy(order);
    } else if (!order->buyOrSell && order->limit <= this->lowestSell->limitPrice) {
        // liquidity taking sell order - walk the buy book
        this->executeSell(order);
    }

    // add idNumber to hash map for cancelling
    this->openOrders[order->idNumber] = order;

    // add order to limit or create limit if not already exists
    auto search = this->availableLimits.find(order->limit);
    if (search == this->availableLimits.end()) {
        // limit doesn't currently exist - create and add to correct book with order
        Limit tempLimit = Limit(order->limit, 1);
        tempLimit.setHeadOrder(order);
        tempLimit.setTailOrder(order);
        order->buyOrSell ? this->buyHeap.push(&tempLimit) : this->sellHeap.push(&tempLimit);
    } else {
        // limit does exist, append order to end of open orders
        Limit* tempLimit = search->second;
        order->setParentLimit(tempLimit);

        Order* tempOrder = tempLimit->getTailOrder();
        order->setPrevOrder(tempOrder);
        tempOrder->setNextOrder(order);
    }
};

void Book::cancel(int idNumber) {
    // get order object
    Order* order = this->openOrders[idNumber];
    Order* prevOrder = order->getPrevOrder();
    Order* nextOrder = order->getNextOrder();

    // if not the first order of limit, update previous order to point to next order
    if (prevOrder) prevOrder->setNextOrder(nextOrder);
    
    // if not the last order of limit, update next order to point to previous order
    if (nextOrder) nextOrder->setPrevOrder(prevOrder);

    // free order from memory
    delete order;
};

/*
Execution code does not notify owners of outstanding limit orders when their order is fully or partially filled, choice made
to not include such capabilities in the scope of this project but can be extended later on
*/

void Book::executeBuy(Order* order) {
    // walk sell book until order is fully filled
    int sharesRemaining = order->shares;
    int totalCost = 0;
    Limit* tempLimit = this->sellHeap.top();
    while (sharesRemaining > 0) {
        if (tempLimit->totalVolume < sharesRemaining) {
            // all shares can be filled at current limit price
            Order* tempOrder;
            while (sharesRemaining > 0) {
                // get next order
                tempOrder = tempLimit->getHeadOrder();
                
                // fill as many shares as needed
                if (tempOrder->shares < sharesRemaining) {
                    // limit order is fully filled by new order, remove from book
                    sharesRemaining -= tempOrder->shares; // update number of shares still need to be filled
                    tempLimit->setHeadOrder(tempOrder->getNextOrder()); // update orders at current limit
                    delete tempOrder; // free order from memory
                } else {
                    // limit order is partially filled by new order, leave order in book w/ updated shares outstanding
                    tempOrder->shares -= sharesRemaining;
                    sharesRemaining = 0;
                }                
            }
            tempLimit->totalVolume -= order->shares;
        } else {
            // not enough volume at current limit, fill all outstanding
            Order* currentOrder = tempLimit->getHeadOrder();
            Order* nextOrder;
            while (currentOrder) {
                sharesRemaining -= currentOrder->shares;
                nextOrder = currentOrder->getNextOrder(); // get next order at limit price
                delete currentOrder; // remove current order
                currentOrder = nextOrder;
            }
            // no memory freeing needed here becuase currentOrder and nextOrder should both be null to get to this point

            // all orders at current limit filled, move onto next one, remove current
            this->sellHeap.pop();
            tempLimit = this->sellHeap.top();

            // optimization possible to make it so limits persist with 0 volume for a set period of time so not to always
            // delete/recreate Limits
        }
    }
    if (tempLimit->totalVolume == 0) delete tempLimit; // free memory used
};

void Book::executeSell(Order* order) {
    // walk buy book until order is fully filled
    int sharesRemaining = order->shares;
    int totalCost = 0;
    Limit* tempLimit = this->buyHeap.top();
    while (sharesRemaining > 0) {
        if (tempLimit->totalVolume < sharesRemaining) {
            // all shares can be filled at current limit price
            Order* tempOrder;
            while (sharesRemaining > 0) {
                // get next order
                tempOrder = tempLimit->getHeadOrder();
                
                // fill as many shares as needed
                if (tempOrder->shares < sharesRemaining) {
                    // limit order is fully filled by new order, remove from book
                    sharesRemaining -= tempOrder->shares; // update number of shares still need to be filled
                    tempLimit->setHeadOrder(tempOrder->getNextOrder()); // update orders at current limit
                    delete tempOrder; // free order from memory
                } else {
                    // limit order is partially filled by new order, leave order in book w/ updated shares outstanding
                    tempOrder->shares -= sharesRemaining;
                    sharesRemaining = 0;
                }                
            }
            tempLimit->totalVolume -= order->shares;
        } else {
            // not enough volume at current limit, fill all outstanding
            Order* currentOrder = tempLimit->getHeadOrder();
            Order* nextOrder;
            while (currentOrder) {
                sharesRemaining -= currentOrder->shares;
                nextOrder = currentOrder->getNextOrder(); // get next order at limit price
                delete currentOrder; // remove current order
                currentOrder = nextOrder;
            }
            // no memory freeing needed here becuase currentOrder and nextOrder should both be null to get to this point

            // all orders at current limit filled, move onto next one, remove current
            this->buyHeap.pop();
            tempLimit = this->buyHeap.top();

            // optimization possible to make it so limits persist with 0 volume for a set period of time so not to always
            // delete/recreate Limits
        }
    }
    if (tempLimit->totalVolume == 0) delete tempLimit; // free memory used
};