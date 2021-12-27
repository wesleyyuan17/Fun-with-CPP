#pragma once
#include<assert.h>
#include "lob.hpp"

Order::Order(int idNumber, bool buyOrSell, int shares, int limit) {
    // set instance variables
    this->idNumber = idNumber;
    this->buyOrSell = buyOrSell;
    this->shares = shares;
    this->limit = limit;

    // set times to -1 and pointers to be null for now
    this->entryTime = -1;
    this->eventTime = -1;
    this->nextOrder = nullptr;
    this->prevOrder = nullptr;
    this->parentLimit = nullptr;
};

void Order::setEntryTime(int entryTime) {
    this->entryTime =entryTime;
};

void Order::setEventTime(int eventTime) {
    this->eventTime = eventTime;
};

void Order::setNextOrder(Order* order) {
    assert(order->limit == this->limit); // adding to right linked list of limit orders
    this->nextOrder = order;
};

void Order::setPrevOrder(Order* order) {
    assert(order->limit == this->limit); // adding to right linked list of limit orders
    this->prevOrder = order;
};

void Order::setParentLimit(Limit* limit) {
    assert(limit->limitPrice == this->limit); // adding to right linked list of limit orders
    this->parentLimit = limit;
};

int Order::getEntryTime() {
    return this->entryTime;
};

int Order::getEventTime() {
    return this->eventTime;
};

Order* Order::getNextOrder() {
    return this->nextOrder;
};

Order* Order::getPrevOrder() {
    return this->prevOrder;
};

Limit* Order::getParentLimit() {
    return this->parentLimit;
};
