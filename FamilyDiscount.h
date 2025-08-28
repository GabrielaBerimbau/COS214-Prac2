#ifndef FAMILYDISCOUNT_H
#define FAMILYDISCOUNT_H

#include "DiscountStrategy.h"

#include <string>
using namespace std;

class FamilyDiscount : public DiscountStrategy {
    public:
        //constructors
        FamilyDiscount();
        virtual ~FamilyDiscount() = default;

        virtual double applyDiscount() override;

};

#endif // FamilyDiscount