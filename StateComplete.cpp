#include "StateComplete.h"
#include "ContextState.h"
#include <iostream>

void StateComplete::handleChange(ContextState* context) {
    std::cout << "In Complete state: Order is finished. Read-only access.\n";
    std::cout << "Order is complete - no further actions available.\n";
}

void StateComplete::addPizza(ContextState* context, Pizza* pizza) {
    // Cannot modify completed order
    std::cout << "Cannot add pizza to completed order.\n";
}

void StateComplete::removePizza(ContextState* context, Pizza* pizza) {
    // Cannot modify completed order
    std::cout << "Cannot remove pizza from completed order.\n";
}

void StateComplete::proceedToReview(ContextState* context) {
    // Cannot transition from complete state
    std::cout << "Cannot review completed order.\n";
}

void StateComplete::backToEditing(ContextState* context) {
    // Cannot transition from complete state
    std::cout << "Cannot edit completed order.\n";
}

void StateComplete::confirmOrder(ContextState* context) {
    // Cannot transition from complete state
    std::cout << "Order is already completed.\n";
}

void StateComplete::completeOrder(ContextState* context) {
    // Already complete
    std::cout << "Order is already complete.\n";
    context->internalDisplayOrder();
}