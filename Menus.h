#ifndef MENUS_H
#define MENUS_H

#include "Observer.h"
#include "Pizza.h"
#include <vector>
#include <string>


class Menus {
protected:
    std::vector<Observer*> observers;
    std::vector<Pizza*> pizzas; 
    
public:
    virtual ~Menus();
    
   
    virtual void addObserver(Observer* observer);
    virtual void removeObserver(Observer* observer);
    
 
    virtual void addPizza(Pizza* pizza);
    virtual void removePizza(Pizza* pizza);
    virtual void removePizzaByName(const std::string& pizzaName);
    
    
    virtual void notifyObservers(const std::string& message) = 0;
    
   
    const std::vector<Pizza*>& getPizzas() const;
    Pizza* getPizzaByName(const std::string& name) const;
    virtual std::string getMenuType() const = 0;
    
   
    void displayMenu() const;
    double getTotalMenuValue() const;
};

#endif 