#pragma once
#include<assert.h>
#include "lob.hpp"

Book::Book() {
    // set pointers to be null for now
    this->buyTree = nullptr;
    this->sellTree = nullptr;
    this->lowestSell = nullptr;
    this->highestBuy = nullptr;
}

void Book::add(Order* order) {

};

void Book::cancel(Order* order) {

};

void Book::execute() {

};