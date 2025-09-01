#include "BasePizza.h"
#include <iostream>
using namespace std;

double BasePizza::getPrice()
{
    //basic pizza ingredients
    double price = 0.0;
    double dough = 10.00;
    double tomatoSauce = 5.00;
    double cheese = 15.00;

    price += dough + tomatoSauce + cheese + toppings->getPrice();

    return price;
}

string BasePizza::getName()
{
    return toppings->getName();
}
