#ifndef TOPPING_H
#define TOPPING_H

#include "PizzaComponent.h"

#include <string>

//individual ingredients
class Topping : public PizzaComponent{
    public:
        //constructors
        Topping(const std::string& n, double p) : PizzaComponent(n, p) {} 
        virtual ~Topping() = default;
        
        virtual std::string getName() override;
        virtual double getPrice() override;

};

#endif // Topping