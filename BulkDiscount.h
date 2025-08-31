#ifndef BULKDISCOUNT_H
#define BULKDISCOUNT_H

#include "DiscountStrategy.h"

#include <string>
using namespace std;

class BulkDiscount : public DiscountStrategy {
    public:
        //constructors
        BulkDiscount();
        virtual ~BulkDiscount() = default;

        virtual double applyDiscount(double originalPrice, int numPizzas) override;

};

#endif // BulkDiscount