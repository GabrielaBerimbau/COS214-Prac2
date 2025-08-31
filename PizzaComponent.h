#ifndef PIZZA_COMPONENT_H
#define PIZZA_COMPONENT_H

#include <string>

class PizzaComponent {
    protected:
        std::string name;
        double price;
    
    public:
        //constructors
        PizzaComponent(const std::string& n, double p) : name(n), price(p) {};
        virtual ~PizzaComponent() = default;

        //composite design methods
        virtual void add(PizzaComponent*) {};
        virtual void removeLast() {};

        virtual std::string getName() = 0;
        virtual double getPrice() = 0;

};

#endif // PizzaComponent