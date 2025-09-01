#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Observer.h"
#include <string>

class Customer : public Observer {
private:
    std::string name;
    
public:
    Customer(const std::string& customerName);
    void update(const std::string& message) override;
    std::string getName() const;
};

#endif 