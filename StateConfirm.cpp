#include "StateConfirm.h"
#include "ContextState.h"
#include "StateComplete.h"
#include <iostream>

void StateConfirm::handleChange(ContextState* context) {
    std::cout << "In Confirmed state: Order is being prepared. You can complete when ready.\n";
    std::cout << "Available actions: completeOrder()\n";
}

void StateConfirm::addPizza(ContextState* context, Pizza* pizza) {
    // Cannot modify order once confirmed
    std::cout << "Cannot add pizza to confirmed order. Order is being prepared.\n";
}

void StateConfirm::removePizza(ContextState* context, Pizza* pizza) {
    // Cannot modify order once confirmed
    std::cout << "Cannot remove pizza from confirmed order. Order is being prepared.\n";
}

void StateConfirm::proceedToReview(ContextState* context) {
    // Cannot go back to review from confirmed state
    std::cout << "Cannot return to review from confirmed order.\n";
}

void StateConfirm::backToEditing(ContextState* context) {
    // Cannot go back to editing from confirmed state
    std::cout << "Cannot return to editing from confirmed order.\n";
}

void StateConfirm::confirmOrder(ContextState* context) {
    // Already confirmed
    std::cout << "Order is already confirmed and being prepared.\n";
}

void StateConfirm::completeOrder(ContextState* context) {
    // StateConfirm can transition to StateComplete
    context->setState(new StateComplete());
    std::cout << "Order completed! Thank you for choosing Romeo's Pizza!\n";
    context->internalDisplayOrder();
}