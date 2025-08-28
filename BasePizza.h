#ifndef BASEPIZZA_H
#define BASEPIZZA_H

#include "Pizza.h"
#include "PizzaComponent.h"

#include <string>
using namespace std;

class BasePizza : public Pizza {
    private :
        PizzaComponent* toppings;

    public:
        BasePizza(PizzaComponent* t) : toppings(t) {};
        virtual ~BasePizza() = default;
        virtual double getPrice() override;
        virtual string getName() override;

};

#endif // BasePizza