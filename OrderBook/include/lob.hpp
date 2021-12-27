#pragma once

// by default class members are private so don't need to add private

class Order; // defined below, otherwise error at compile time b/c Limit has Order pointers before Order is defined

class Limit {
    // representing a single limit price
    Limit* parent;
    Limit* leftChild;
    Limit* rightChild;
    Order* headOrder;
    Order* tailOrder;

    public:
        Limit(int limitPrice, int volume);
        
        void setParent(Limit* parent);
        void setLeftChild(Limit* child);
        void setRightChild(Limit* child);
        void setHeadOrder(Order* order);
        void setTailOrder(Order* order);

        Limit* getParent();
        Limit* getLeftChild();
        Limit* getRightChild();
        Order* getHeadOrder();
        Order* getTailOrder();

        int limitPrice;
        int size;
        int totalVolume;
};


class Order {
    int entryTime;
    int eventTime;
    Order* nextOrder;
    Order* prevOrder;
    Limit* parentLimit;

    public:
        Order(int idNumber, bool buyOrSell, int shares, int limit);

        void setEntryTime(int entryTime);
        void setEventTime(int eventTime);
        void setNextOrder(Order* order);
        void setPrevOrder(Order* order);
        void setParentLimit(Limit* limit);

        int getEntryTime();
        int getEventTime();
        Order* getNextOrder();
        Order* getPrevOrder();
        Limit* getParentLimit();

        int idNumber;
        bool buyOrSell;
        int shares;
        int limit;
};


class Book {
    Limit* buyTree;
    Limit* sellTree;
    Limit* lowestSell;
    Limit* highestBuy;

    public:
        Book();
        void add(Order* order);
        void cancel(Order* order);
    
    private:
        void execute();
};