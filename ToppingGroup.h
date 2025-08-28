#ifndef TOPPINGGROUP_H
#define TOPPINGGROUP_H

#include "PizzaComponent.h"

#include <string>
using namespace std;

class ToppingGroup : public PizzaComponent{
    private:
        PizzaComponent* toppings;
        double price;
        string name;

    public:
        ToppingGroup(PizzaComponent* t, double p, string n) : PizzaComponent(p, n), toppings(t) {};
        virtual ~ToppingGroup() = default;

        //inherited functions
        virtual string getName() override;
        virtual double getPrice() override;

        //class specific
        void add(PizzaComponent* component);

};

#endif // ToppingGroup