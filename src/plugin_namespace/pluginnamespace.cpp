// Copyright (c) 2014, Sam Crow samcrow@uw.edu
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies,
// either expressed or implied, of the FreeBSD Project.

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
