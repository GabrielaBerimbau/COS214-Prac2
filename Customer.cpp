#include "Customer.h"
#include <iostream>

Customer::Customer(const std::string& customerName) : name(customerName) {
}

void Customer::update(const std::string& message) {
    std::cout << "[CUSTOMER " << name << "]: Received notification - " << message << std::endl;
    
    // Customer-specific reaction
    if (message.find("NEW PIZZA") != std::string::npos) {
        std::cout << "[CUSTOMER " << name << "]: Great! I'll check out this new pizza option!\n";
    } else if (message.find("REMOVED") != std::string::npos) {
        std::cout << "[CUSTOMER " << name << "]: Oh no, one of my options is gone. I'll look for alternatives.\n";
    }
}

std::string Customer::getName() const {
    return name;
}