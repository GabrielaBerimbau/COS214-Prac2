#include "PizzaDecorator.h"
#include <iostream>
using namespace std;

PizzaDecorator::~PizzaDecorator()
{
    delete pizza;
}

double PizzaDecorator::getPrice()
{
    return pizza->getPrice();
}

string PizzaDecorator::getName()
{
    return pizza->getName();
}
