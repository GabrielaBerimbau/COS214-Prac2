#include "PizzaDecorator.h"
#include <iostream>
using namespace std;

double PizzaDecorator::getPrice()
{
    return pizza->getPrice();
}

string PizzaDecorator::getName()
{
    return pizza->getName();
}
