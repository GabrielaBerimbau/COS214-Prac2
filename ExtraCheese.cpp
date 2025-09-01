#include "ExtraCheese.h"
#include <iostream>

double ExtraCheese::getPrice()
{
    return PizzaDecorator::getPrice() + 12.00;
}

std::string ExtraCheese::getName()
{
    return PizzaDecorator::getName() + ", Extra Cheese";
}

