#ifndef PLUGINNAMESPACE_H
#define PLUGINNAMESPACE_H
#include "../namespaces.h"
#include <initializer_list>
#include <vector>
#include "pathcomponent.h"

namespace PPLNAMESPACE {

class PluginNamespace
{
public:
    PluginNamespace(std::initializer_list<std::string> components);
    
    std::string path();
    
    static void setOuterNamespace(std::initializer_list<std::string> components);
    
private:
    
    
    static std::vector<PathComponent> outerComponents;
    
    std::vector<PathComponent> components_;
    
    
    /**
     * @brief Determines if the given string is a valid
     * command or dataref path.
     * @param path
     * @return 
     */
    static bool isValidPath(const std::string& path);
};

}
#endif // PLUGINNAMESPACE_H
