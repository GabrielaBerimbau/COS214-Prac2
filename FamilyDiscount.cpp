#include "FamilyDiscount.h"
#include <iostream>
using namespace std;

double FamilyDiscount::applyDiscount(double originalPrice, int numPizzas)
{
    double discount = originalPrice * 0.15;
    return originalPrice - discount;
}
