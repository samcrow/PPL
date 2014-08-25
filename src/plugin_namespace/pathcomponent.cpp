#include "pathcomponent.h"
#include <stdexcept>
#include <cctype>
#include <stdexcept>

namespace PPLNAMESPACE {

PathComponent::PathComponent(std::string raw) :
    raw_(raw),
    sanitized_(sanitize(raw))
{
}

PathComponent::PathComponent(std::string raw, std::string sanitized) :
    raw_(raw),
    sanitized_(sanitized)
{
    if(!isValidComponent(sanitized)) {
        throw std::invalid_argument("PathComponent: Provided sanitized string is not a valid component");
    }
}

std::string PathComponent::sanitized() const
{
    return sanitized_;
}

std::string PathComponent::sanitize(const std::string &raw) {
    
    std::string sanitized;
    sanitized.reserve(raw.length());
    
    // 1: Replace uppercase letters with lowercase letters
    for(const char character : raw) {
        if(std::isupper(character)) {
            sanitized.push_back(char(std::tolower(character)));
        }
        else {
            sanitized.push_back(char(character));
        }
    }
    
    // 2: Collapse spaces and dashes into underscores
    const std::regex spaceCollapsor("[\\s-]+");
    sanitized = std::regex_replace(sanitized, spaceCollapsor, "_");
    
    // 3: Remove any other characters
    const std::regex otherChars("[^a-zA-Z0-9_]+");
    sanitized = std::regex_replace(sanitized, otherChars, "");
    
    return sanitized;
}

bool PathComponent::isValidComponent(const std::string& component) {
    const std::regex validator("^[a-zA-Z0-9_]+$");
    return std::regex_match(component, validator);
}

}
