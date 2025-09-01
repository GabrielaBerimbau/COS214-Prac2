#include "BulkDiscount.h"
#include <iostream>

double BulkDiscount::applyDiscount(double originalPrice, int numPizzas)
{
    if (numPizzas < 5) {
        std::cout << "Bulk discount cannot be applied to orders with 5 or more pizzas.";
        return originalPrice;
    }

    double discount = originalPrice * 0.10;

    return (originalPrice - discount);
}
