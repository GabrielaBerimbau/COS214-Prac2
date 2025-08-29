#ifndef TOPPINGGROUP_H
#define TOPPINGGROUP_H

#include "PizzaComponent.h"

#include <vector>
#include <string>

//holds individual and group toppings
class ToppingGroup : public PizzaComponent{
    private:
        std::vector<PizzaComponent*> toppings;

    public:
        // Group name for toppings
        ToppingGroup(const std::string& groupName) : PizzaComponent(groupName, 0.0) {}
        // With initial toppings
        ToppingGroup(const std::string& groupName, const std::vector<PizzaComponent*>& initialToppings) : PizzaComponent(groupName, 0.0), toppings(initialToppings) {}
        virtual ~ToppingGroup() = default;

        //inherited functions
        virtual std::string getName() override;
        virtual double getPrice() override;

        //class specific
        void add(PizzaComponent* component);
        void removeLast();

};

#endif // ToppingGroup