#include "ContextState.h"
#include "StateOrder.h"
#include "StateReview.h"
#include "StateConfirm.h"
#include "StateComplete.h"
#include "Pizza.h"
#include "DiscountStrategy.h"
#include "RegularPrice.h"
#include "BulkDiscount.h"
#include "FamilyDiscount.h"
#include <iostream>
#include <algorithm>

ContextState::ContextState() : orderNumber(0) {
    state = new StateOrder(); 
    strategy = new RegularPrice();
    std::cout << "New order created in " << state->getStateName() << " state.\n";
}

ContextState::~ContextState() {
    //clean up all pizzas in the order
    for (Pizza* pizza : pizzas) {
        delete pizza;
    }
    pizzas.clear();
    
    delete state; 
    delete strategy;
}

void ContextState::setState(State* newState) {
    if (state != newState && newState != nullptr) {
        std::cout << "Order state changed from " << state->getStateName() 
                  << " to " << newState->getStateName() << "\n";
        delete state;
        state = newState; 
    }
}

State* ContextState::getCurrentState() const {
    return state;
}

void ContextState::addPizza(Pizza* pizza) {
    state->addPizza(this, pizza);
}

void ContextState::removePizza(Pizza* pizza) {
    state->removePizza(this, pizza);
}

void ContextState::proceedToReview() {
    state->proceedToReview(this);
}

void ContextState::backToEditing() {
    state->backToEditing(this);
}

void ContextState::confirmOrder() {
    state->confirmOrder(this);
}

void ContextState::completeOrder() {
    state->completeOrder(this);
}

// Helper methods for states to modify order data
void ContextState::internalAddPizza(Pizza* pizza) {
    if (pizza != nullptr) {
        pizzas.push_back(pizza);
        std::cout << "Added pizza to order.\n"; 
    }
}

void ContextState::internalRemovePizza(Pizza* pizza) {
    auto it = std::find(pizzas.begin(), pizzas.end(), pizza);
    if (it != pizzas.end()) {
        pizzas.erase(it);
        std::cout << "Removed pizza from order.\n";
    } else {
        std::cout << "Pizza not found in order.\n";
    }
}

void ContextState::internalDisplayOrder() const {
    std::cout << "\n--- Order #" << orderNumber << " (" << state->getStateName() << ") ---\n";
    if (pizzas.empty()) {
        std::cout << "No pizzas in order.\n";
    } else {
        std::cout << "Pizzas:\n";
        for (Pizza* pizza : pizzas) {
            cout << "- " << pizza->getName() << " - R" << pizza->getPrice() << endl;
        }
    }
    std::cout << "Total: R" << getTotalPrice() << "\n";
    std::cout << "Total after discount: R" << strategy->applyDiscount(getTotalPrice(), pizzas.size()) << "\n";
    std::cout << "------------------------\n\n";
}

void ContextState::setStrategy(DiscountStrategy * discountStrategy)
{
    delete strategy;
    strategy = discountStrategy;
}

const std::vector<Pizza*>& ContextState::getPizzas() const {
    return pizzas;
}

double ContextState::getTotalPrice() const {
    double total = 0.0;
    for (std::vector<Pizza*>::const_iterator it = pizzas.begin(); it != pizzas.end(); ++it) {
        if (*it != nullptr) {
            total += (*it)->getPrice();
        }
    }
    return total;
}

int ContextState::getOrderNumber() const {
    return orderNumber;
}

void ContextState::setOrderNumber(int number) {
    orderNumber = number;
}
