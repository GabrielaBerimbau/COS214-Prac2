#ifndef STUFFEDCRUST_H
#define STUFFEDCRUST_H

#include "PizzaDecorator.h"

#include <string>
using namespace std;

class StuffedCrust : public PizzaDecorator {
    public:
        //constructors
        StuffedCrust(Pizza* pizza) : PizzaDecorator(pizza) {};
        virtual ~StuffedCrust() = default;

        //inherited functions
        virtual double getPrice() override;
        virtual string getName() override;


};

#endif // StuffedCrust