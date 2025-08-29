#include "ToppingGroup.h"
#include <iostream>
using namespace std;

string ToppingGroup::getName()
{
    std::string res = name + " (";

    std::vector<PizzaComponent*>::iterator it;
    for (it = toppings.begin(); it != toppings.end(); ++it) {
        res += (*it)->getName();
        if (it != toppings.end() - 1) {
            res += ", ";
        }
    }
    res += ")";
    return res;
}

double ToppingGroup::getPrice()
{
    double price = 0.0;

    std::vector<PizzaComponent*>::iterator it;
    for (it = toppings.begin(); it != toppings.end(); ++it) {
        price += (*it)->getPrice();
    }

    return price;
}

void ToppingGroup::add(PizzaComponent *component)
{
    if (component == nullptr) {
        return;
    }

    toppings.push_back(component);
}

void ToppingGroup::removeLast()
{
    if (!toppings.empty()) {
        delete toppings.back();
        toppings.pop_back();
    }
}
