#pragma once

// by default class members are private so don't need to add private

class Limit {
    // representing a single limit price
    Limit *parent;
    Limit *leftChild;
    Limit *rightChild;
    Order *headOrder;
    Order *tailOrder;

    public:
        Limit(int limitPrice, int volume);

        int limitPrice;
        int size;
        int totalVolume;
};


class Order {
    int entryTime;
    int eventTime;
    Order *nextOrder;
    Order *prevOrder;
    Limit *parentLimit;

    public:
        Order(bool buyOrSell, int shares, int limit);

        int idNumber;
        bool buyOrSell;
        int shares;
        int limit;
};


class Book {
    Limit *buyTree;
    Limit *sellTree;
    Limit *lowestSell;
    Limit *highestBuy;

    public:
        Book();
        void add();
        void cancel();
        void execute();
};