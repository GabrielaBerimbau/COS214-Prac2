#include "Menus.h"
#include <algorithm>
#include <iostream>

Menus::~Menus() {
    // Clean up pizza objects
    //check this
    for (std::vector<Pizza*>::iterator it = pizzas.begin(); it != pizzas.end(); ++it) {
        delete *it;
    }
    pizzas.clear();
}

void Menus::addObserver(Observer* observer) {
    if (observer != NULL) {
        observers.push_back(observer);
        std::cout << "Observer added to " << getMenuType() << "\n";
    }
}

void Menus::removeObserver(Observer* observer) {
    std::vector<Observer*>::iterator it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
        std::cout << "Observer removed from " << getMenuType() << "\n";
    }
}

void Menus::addPizza(Pizza* pizza) {
    if (pizza != NULL) {
        pizzas.push_back(pizza);
        std::cout << "Added " << pizza->getName() << " (R" << pizza->getPrice() << ") to " << getMenuType() << "\n";
        
        // Notify observers about the addition
        std::string message = "NEW PIZZA: " + pizza->getName() + " has been added to " + getMenuType() + " for R" + std::to_string(pizza->getPrice());
        notifyObservers(message);
    }
}

void Menus::removePizza(Pizza* pizza) {
    if (pizza == NULL) return;
    
    std::vector<Pizza*>::iterator it = std::find(pizzas.begin(), pizzas.end(), pizza);
    if (it != pizzas.end()) {
        std::string pizzaName = pizza->getName();
        std::cout << "Removed " << pizzaName << " from " << getMenuType() << "\n";
        
        pizzas.erase(it);
        // don't delete the pizza here as it might be used elsewhere
        
        // Notify observers about the removal
        std::string message = "REMOVED: " + pizzaName + " has been removed from " + getMenuType();
        notifyObservers(message);
    } else {
        std::cout << "Pizza not found in " << getMenuType() << "\n";
    }
}

void Menus::removePizzaByName(const std::string& pizzaName) {
    for (std::vector<Pizza*>::iterator it = pizzas.begin(); it != pizzas.end(); ++it) {
        if ((*it)->getName() == pizzaName) {
            std::cout << "Removed " << pizzaName << " from " << getMenuType() << "\n";
            
            delete *it; // Delete the pizza object
            pizzas.erase(it);
            
            // Notify observers about the removal
            std::string message = "REMOVED: " + pizzaName + " has been removed from " + getMenuType();
            notifyObservers(message);
            return;
        }
    }
    std::cout << "Pizza " << pizzaName << " not found in " << getMenuType() << "\n";
}

const std::vector<Pizza*>& Menus::getPizzas() const {
    return pizzas;
}

Pizza* Menus::getPizzaByName(const std::string& name) const {
    for (std::vector<Pizza*>::const_iterator it = pizzas.begin(); it != pizzas.end(); ++it) {
        if ((*it)->getName().find(name) != std::string::npos) {
            return *it;
        }
    }
    return NULL;
}

void Menus::displayMenu() const {
    std::cout << "\n=== " << getMenuType() << " ===\n";
    if (pizzas.empty()) {
        std::cout << "No pizzas available.\n";
    } else {
        for (size_t i = 0; i < pizzas.size(); ++i) {
            std::cout << (i + 1) << ". " << pizzas[i]->getName() << " - R" << pizzas[i]->getPrice() << "\n";
        }
    }
    std::cout << "Total menu value: R" << getTotalMenuValue() << "\n";
    std::cout << "=========================\n\n";
}

double Menus::getTotalMenuValue() const {
    double total = 0.0;
    for (std::vector<Pizza*>::const_iterator it = pizzas.begin(); it != pizzas.end(); ++it) {
        total += (*it)->getPrice();
    }
    return total;
}