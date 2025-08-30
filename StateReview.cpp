#include "StateReview.h"
#include "ContextState.h"
#include "StateOrder.h"
#include "StateConfirm.h"
#include <iostream>

void StateReview::handleChange(ContextState* context) {
    std::cout << "In Review state: Review your order and confirm or go back to edit.\n";
    std::cout << "Available actions: confirmOrder(), backToEditing()\n";
    context->internalDisplayOrder();
}

void StateReview::addPizza(ContextState* context, Pizza* pizza) {
    // Cannot add pizzas in Review state
    std::cout << "Cannot add pizza in Review state. Please go back to editing first.\n";
}

void StateReview::removePizza(ContextState* context, Pizza* pizza) {
    // Cannot remove pizzas in Review state
    std::cout << "Cannot remove pizza in Review state. Please go back to editing first.\n";
}

void StateReview::proceedToReview(ContextState* context) {
    // Already in Review state
    std::cout << "Already in Review state.\n";
    context->internalDisplayOrder();
}

void StateReview::backToEditing(ContextState* context) {
    // StateReview can go back to StateOrder
    context->setState(new StateOrder());
    std::cout << "Returning to edit order...\n";
}

void StateReview::confirmOrder(ContextState* context) {
    // StateReview can transition to StateConfirm
    context->setState(new StateConfirm());
    std::cout << "Order confirmed! Your order is being prepared...\n";
}

void StateReview::completeOrder(ContextState* context) {
    // Cannot complete directly from Review state, must confirm first
    std::cout << "Cannot complete order from Review state. Please confirm first.\n";
}