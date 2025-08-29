#include "Pizza.h"
#include <iostream>

void Pizza::printPizza()
{
    std::cout << "Printing Pizza Order: " << endl;
    cout << getName() <<  " - " << "R" << getPrice() << endl;

}
