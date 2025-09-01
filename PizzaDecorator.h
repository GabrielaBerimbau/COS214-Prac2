#ifndef PIZZADECORATOR_H
#define PIZZADECORATOR_H

#include "Pizza.h"

#include <string>
using namespace std;

class PizzaDecorator : public Pizza {
    private :
        Pizza* pizza;

    public:
        //constructors
        PizzaDecorator(Pizza* p) : pizza(p) {};
        virtual ~PizzaDecorator() = default;

        //inherited functions
        virtual double getPrice() override;
        virtual string getName() override;

};

#endif // PizzaDecorator