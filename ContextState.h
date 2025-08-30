#ifndef CONTEXTSTATE_H
#define CONTEXTSTATE_H

#include "State.h"
#include <vector>
#include <string>


class Pizza;


class ContextState {
private:
    State* state;
    std::vector<Pizza*> pizzas; 
    int orderNumber;
    
public:
    ContextState();
    ~ContextState();
    
    // State management
    void setState(State* newState);
    State* getCurrentState() const;
    
    
    void addPizza(Pizza* pizza);
    void removePizza(Pizza* pizza);
    void proceedToReview();
    void backToEditing();
    void confirmOrder();
    void completeOrder();
    
   
    const std::vector<Pizza*>& getPizzas() const;
    double getTotalPrice() const;
    int getOrderNumber() const;
    void setOrderNumber(int number);
    
  //helper methods
    void internalAddPizza(Pizza* pizza);
    void internalRemovePizza(Pizza* pizza);
    void internalDisplayOrder() const;
};

#endif 