#ifndef STATECONFIRM_H
#define STATECONFIRM_H

#include "State.h"

// Forward declaration
class Pizza;

class StateConfirm : public State {
public:
    void handleChange(ContextState* context) override;
    std::string getStateName() const override { return "Confirmed"; }
    
    void addPizza(ContextState* context, Pizza* pizza) override;
    void removePizza(ContextState* context, Pizza* pizza) override;
    void proceedToReview(ContextState* context) override;
    void backToEditing(ContextState* context) override;
    void confirmOrder(ContextState* context) override;
    void completeOrder(ContextState* context) override;
};

#endif 