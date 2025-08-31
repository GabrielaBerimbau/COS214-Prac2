#ifndef REGULARPRICE_H
#define REGULARPRICE_H

#include "DiscountStrategy.h"

#include <string>
using namespace std;

class RegularPrice : public DiscountStrategy {
    public:
        //constructors
        RegularPrice() {};
        virtual ~RegularPrice() = default;

        virtual double applyDiscount(double originalPrice, int numPizzas) override;

};

#endif // RegularPrice