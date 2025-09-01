
#ifndef SPECIALSMENU_H
#define SPECIALSMENU_H

#include "Menus.h"

class SpecialsMenu : public Menus {
public:
    void notifyObservers(const std::string& message) override;
    std::string getMenuType() const override { return "Specials Menu"; }
};

#endif