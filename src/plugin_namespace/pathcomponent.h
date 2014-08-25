#ifndef PATHCOMPONENT_H
#define PATHCOMPONENT_H
#include "../namespaces.h"
#include <string>
#include <regex>

namespace PPLNAMESPACE {

class PathComponent
{
public:
    PathComponent(std::string raw);
    PathComponent(std::string raw, std::string sanitized);
    
    std::string sanitized() const;
    
private:
    
    std::string raw_;
    std::string sanitized_;
    
    /**
     * @brief Sanitizes a string to make it suitable for
     * use as part of a dataref or command identifier.
     * 
     * Because this function removes slashes, it should only be used
     * for components of a path, not for a complete path.
     * 
     * @param raw
     * @return 
     */
    static std::string sanitize(const std::string& raw);
    
    static bool isValidComponent(const std::string& component);
};

}
#endif // PATHCOMPONENT_H
