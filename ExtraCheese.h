#ifndef EXTRACHEESE_H
#define EXTRACHEESE_H

#include "PizzaDecorator.h"

#include <string>
using namespace std;

class ExtraCheese : public PizzaDecorator {
    public:
        //constructors
        ExtraCheese(Pizza* pizza) : PizzaDecorator(pizza) {};
        virtual ~ExtraCheese() = default;

        //inherited functions
        virtual double getPrice() override;
        virtual string getName() override;

};

#endif // ExtraCheese