#ifndef TOPPING_H
#define TOPPING_H

#include "PizzaComponent.h"

#include <string>
using namespace std;

class Topping : public PizzaComponent{
    private :
        double price;
        string name;
    public:
        Topping(double p,  string n) : PizzaComponent(p,n) {};
        virtual ~Topping() = default;
        virtual string getName() override;
        virtual double getPrice() override;

};

#endif // Topping