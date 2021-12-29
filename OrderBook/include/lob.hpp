#pragma once
#include<queue>
#include<map>

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


class LimitGreater {
    public:
        bool operator() (const Limit* thisLimit, const Limit* thatLimit) {
            return thisLimit->limitPrice > thatLimit->limitPrice;
        }
};

class LimitLesser {
    public:
        bool operator() (const Limit* thisLimit, const Limit* thatLimit) {
            return thisLimit->limitPrice < thatLimit->limitPrice;
        }
};

// static bool limitGreater(Limit* thisLimit, Limit* thatLimit) {
//     return thisLimit->limitPrice > thatLimit->limitPrice;
// };


// static bool limitLesser(Limit* thisLimit, Limit* thatLimit) {
//     return thisLimit->limitPrice < thatLimit->limitPrice;
// };


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
        bool buyOrSell; // true is buy, false is sell
        int shares;
        int limit;
};


class Book {
    std::priority_queue<Limit*, std::vector<Limit*>, LimitLesser> buyHeap; // min-heap of buy orders
    std::priority_queue<Limit*, std::vector<Limit*>, LimitGreater> sellHeap; // max-heap of sell orders
    std::map<int, Order*> openOrders;
    std::map<int, Limit*> availableLimits;
    Limit* highestBuy;
    Limit* lowestSell;

    public:
        Book();
        void add(Order* order); // can be changed to return success/failure of add
        void cancel(int idNumber); // can be changed to return success/failure of cancel
    
    private:
        // void execute(Order* order);
        void executeBuy(Order* order);
        void executeSell(Order* order);
};