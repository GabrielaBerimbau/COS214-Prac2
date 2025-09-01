#ifndef PIZZAMENU_H
#define PIZZAMENU_H

#include "Menus.h"

class PizzaMenu : public Menus {
public:
    void notifyObservers(const std::string& message) override;
    std::string getMenuType() const override { return "Regular Menu"; }
};

#endif 