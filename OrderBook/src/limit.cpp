#pragma once
#include "include/lob.h"

Limit::Limit(int limitPrice, int size) : totalVolume(0) {
    // set instance variables
    this->limitPrice = limitPrice;
    this->size = size;

    // set pointers to be null for now
    this->parent = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    this->headOrder = nullptr;
    this->tailOrder = nullptr;
};

void Limit::setParent(Limit *parent) {
    this->parent = parent;
};

void Limit::setLeftChild(Limit *child) {
    this->leftChild = child;
};

void Limit::setRightChild(Limit *child) {
    this->rightChild = child;
};

void Limit::setHeadOrder(Order *order) {
    this->headOrder = order;
};

void Limit::setTailOrder(Order *order) {
    this->tailOrder = order;
};

Limit * Limit::getParent() {
    return this->parent;
};

Limit * Limit::getLeftChild() {
    return this->leftChild;
};

Limit * Limit::getRightChild() {
    return this->rightChild;
};

Order * Limit::getHeadOrder() {
    return this->headOrder;
};

Order * Limit::getTailOrder() {
    return this->tailOrder;
};