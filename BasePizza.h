#ifndef BASEPIZZA_H
#define BASEPIZZA_H

#include "Pizza.h"
#include "PizzaComponent.h"

#include <string>

class BasePizza : public Pizza {
    private :
        std::string pizzaName;
        PizzaComponent* toppings;

    public:
        BasePizza(std::string n, PizzaComponent* t) : pizzaName(n), toppings(t) {};
        virtual ~BasePizza();

        virtual double getPrice() override;
        virtual std::string getName() override;

};

#endif // BasePizza