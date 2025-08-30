#ifndef STATE_H
#define STATE_H

#include <string>


class ContextState;
class Pizza;


class State {
public:
    virtual ~State() = default;
    virtual void handleChange(ContextState* context) = 0;
    virtual std::string getStateName() const = 0;
    
    // State transition methods 
    virtual void addPizza(ContextState* context, Pizza* pizza) = 0;
    virtual void removePizza(ContextState* context, Pizza* pizza) = 0;
    virtual void proceedToReview(ContextState* context) = 0;
    virtual void backToEditing(ContextState* context) = 0;
    virtual void confirmOrder(ContextState* context) = 0;
    virtual void completeOrder(ContextState* context) = 0;
};

#endif 





