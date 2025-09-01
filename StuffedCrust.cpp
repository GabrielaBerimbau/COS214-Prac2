#include "StuffedCrust.h"
#include <iostream>
using namespace std;

double StuffedCrust::getPrice()
{
    return PizzaDecorator::getPrice() + 20.00;
}

string StuffedCrust::getName()
{
    return PizzaDecorator::getName() + ", Stuffed Crust";
}

