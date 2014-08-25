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

#ifndef PLUGINNAMESPACE_H
#define PLUGINNAMESPACE_H
#include "../namespaces.h"
#include <initializer_list>
#include <vector>
#include "pathcomponent.h"

namespace PPLNAMESPACE {

/**
 * @brief The PluginNamespace class keeps track of a namespace
 * used for datarefs and commands associated with a plugin or a subdivision
 * of a plugin.
 * 
 * The outer namespace applies to all instances of this class. When a new
 * instance is created, it can defined additional namespace segments.
 */
class PluginNamespace
{
public:
    
    /**
     * @brief Creates a sub-namespace with the given components, in addition
     * to the outer namespace components
     * @param components
     */
    PluginNamespace(std::initializer_list<std::string> components);
    
    /**
     * @brief Returns a path that contains the outer namespace components
     * followed by the namespace components associated with this instance.
     * 
     * The returned path will not have a trailing slash.
     * 
     * @return 
     */
    std::string path();
    
    /**
     * @brief Sets the namespace components used for every instance of this class
     * @param components
     */
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
