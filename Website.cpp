#include "Website.h"
#include <iostream>

Website::Website(const std::string& name) : siteName(name) {
}

void Website::update(const std::string& message) {
    std::cout << "[WEBSITE " << siteName << "]: Updating site content - " << message << std::endl;
    
    // Website-specific actions
    if (message.find("NEW PIZZA") != std::string::npos) {
        std::cout << "[WEBSITE " << siteName << "]: Adding new pizza to website menu and featuring it on homepage\n";
        std::cout << "[WEBSITE " << siteName << "]: Sending promotional emails to subscribers\n";
    } else if (message.find("REMOVED") != std::string::npos) {
        std::cout << "[WEBSITE " << siteName << "]: Removing pizza from website and updating inventory\n";
        std::cout << "[WEBSITE " << siteName << "]: Redirecting old pizza links to similar alternatives\n";
    }
}

std::string Website::getSiteName() const {
    return siteName;
}