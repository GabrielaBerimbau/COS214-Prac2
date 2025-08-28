#ifndef STUFFEDCRUST_H
#define STUFFEDCRUST_H

#include "PizzaDecorator.h"

#include <string>
using namespace std;

class StuffedCrust : public PizzaDecorator {
    public:
        //constructors
        StuffedCrust();
        virtual ~StuffedCrust() = default;

        //inherited functions
        virtual double getPrice() override;
        virtual string getName() override;

        //class specific

};

#endif // StuffedCrust