#ifndef DISCOUNTSTRATEGY_H
#define DISCOUNTSTRATEGY_H

#include <string>
using namespace std;

class DiscountStrategy {
    public:
        //constructors
        DiscountStrategy();
        virtual ~DiscountStrategy() = default;

        virtual double applyDiscount(double originalPrice, int numPizzas) = 0; //pass in total order price and number of pizzas in the order 

};

#endif // DiscountStrategy