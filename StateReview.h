#ifndef STATEREVIEW_H
#define STATEREVIEW_H

#include "State.h"


class Pizza;

class StateReview : public State {
public:
    void handleChange(ContextState* context) override;
    std::string getStateName() const override { return "Review"; }
    
    void addPizza(ContextState* context, Pizza* pizza) override;
    void removePizza(ContextState* context, Pizza* pizza) override;
    void proceedToReview(ContextState* context) override;
    void backToEditing(ContextState* context) override;
    void confirmOrder(ContextState* context) override;
    void completeOrder(ContextState* context) override;
};

#endif 

