#include "PizzaMenu.h"
#include <iostream>

void PizzaMenu::notifyObservers(const std::string& message) {
    std::cout << "\n--- " << getMenuType() << " Update ---\n";
    
    for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it) {
        if (*it != NULL) {
            (*it)->update(message);
        }
    }
    
    std::cout << "--- End Update ---\n\n";
}