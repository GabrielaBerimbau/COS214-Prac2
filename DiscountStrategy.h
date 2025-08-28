#ifndef DISCOUNTSTRATEGY_H
#define DISCOUNTSTRATEGY_H

#include <string>
using namespace std;

class DiscountStrategy {
    public:
        //constructors
        DiscountStrategy();
        virtual ~DiscountStrategy() = default;

        virtual double applyDiscount() = 0;

};

#endif // DiscountStrategy