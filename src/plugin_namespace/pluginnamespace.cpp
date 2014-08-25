#include "pluginnamespace.h"
#include <sstream>

namespace PPLNAMESPACE {

std::vector<PathComponent> PluginNamespace::outerComponents;

PluginNamespace::PluginNamespace(std::initializer_list<std::string> components)
{
    for(const std::string& compName : components) {
        components_.emplace_back(compName);
    }
}

std::string PluginNamespace::path() {
    std::stringstream stream;
    for(const PathComponent& component : outerComponents) {
        stream << component.sanitized() << '/';
    }
    for(const PathComponent& component : components_) {
        stream << component.sanitized() << '/';
    }
    // Remove the last slash
    std::string path = stream.str();
    path.erase(path.end() - 1);
    
    // Check the validity of this path
    
    
    return path;
}

void PluginNamespace::setOuterNamespace(std::initializer_list<std::string> components) {
    outerComponents.clear();
    for(const std::string& compName : components) {
        outerComponents.emplace_back(compName);
    }
}



bool PluginNamespace::isValidPath(const std::string &path) {
    const std::regex pathPattern("^[a-zA-Z0-9_]+/([a-zA-Z0-9_]+/)+[a-zA-Z0-9_]+$");
    return std::regex_match(path, pathPattern);
}

}
