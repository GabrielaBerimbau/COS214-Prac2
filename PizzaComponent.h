#ifndef PIZZA_COMPONENT_H
#define PIZZA_COMPONENT_H

#include <string>
using namespace std;

class PizzaComponent {
    private:
        double price;
        string name;
    
    public:
        PizzaComponent(double p, string n) : price(p), name(n) {};
        virtual ~PizzaComponent();
        virtual string getName() = 0;
        virtual double getPrice() = 0;

};

#endif // PizzaComponent