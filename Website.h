#ifndef WEBSITE_H
#define WEBSITE_H

#include "Observer.h"
#include <string>

class Website : public Observer {
private:
    std::string siteName;
    
public:
    Website(const std::string& name);
    void update(const std::string& message) override;
    std::string getSiteName() const;
};

#endif 