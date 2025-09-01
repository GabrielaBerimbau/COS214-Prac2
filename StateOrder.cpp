#include "StateOrder.h"
#include "ContextState.h"
#include "StateReview.h"
#include <iostream>

void StateOrder::handleChange(ContextState* context) {
    (void)context;
    std::cout << "In Order state: You can add/remove pizzas or proceed to review.\n";
    std::cout << "Available actions: addPizza(), removePizza(), proceedToReview()\n";
}

void StateOrder::addPizza(ContextState* context, Pizza* pizza) {
    // StateOrder allows adding pizzas
    context->internalAddPizza(pizza);
}

void StateOrder::removePizza(ContextState* context, Pizza* pizza) {
    // StateOrder allows removing pizzas
    context->internalRemovePizza(pizza);
}

void StateOrder::proceedToReview(ContextState* context) {
    // StateOrder can transition to StateReview
    context->setState(new StateReview());
    std::cout << "Proceeding to review order...\n";
    context->internalDisplayOrder();
}

void StateOrder::backToEditing(ContextState* context) {
    (void)context;
    // Cannot go back to editing from Order state
    std::cout << "Cannot return to editing - already in Order state.\n";
}

void StateOrder::confirmOrder(ContextState* context) {
    (void)context;
    // Cannot confirm directly from Order state 
    std::cout << "Cannot confirm order directly from Order state. Please review first.\n";
}

void StateOrder::completeOrder(ContextState* context) {
    (void)context;
    // Cannot complete directly from Order state
    std::cout << "Cannot complete order from Order state. Must confirm first.\n";
}
