#include "SpecialsMenu.h"
#include <iostream>

void SpecialsMenu::notifyObservers(const std::string& message) {
    std::cout << "\n " << getMenuType() << " Alert! \n";
    
    for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it) {
        if (*it != NULL) {
            (*it)->update(message);
        }
    }
    
    std::cout << "--- End Special Alert ---\n\n";
}