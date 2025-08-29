#ifndef PIZZA_H
#define PIZZA_H

#include <string>
using namespace std;

class Pizza {
    public:
        //constructors
        Pizza() {};
        virtual ~Pizza() = default;

        virtual double getPrice() = 0;
        virtual string getName() = 0;
        virtual void printPizza();

};

#endif // Pizza