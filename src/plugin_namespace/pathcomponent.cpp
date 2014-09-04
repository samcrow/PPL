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
    sanitized = std::regex_replace(sanitized, spaceCollapsor, std::string("_"));
    
    // 3: Remove any other characters
    const std::regex otherChars("[^a-zA-Z0-9_]+");
    sanitized = std::regex_replace(sanitized, otherChars, std::string(""));
    
    return sanitized;
}

bool PathComponent::isValidComponent(const std::string& component) {
    const std::regex validator("^[a-zA-Z0-9_]+$");
    return std::regex_match(component, validator);
}

}
