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

#include "airport.h"
#include <stdexcept>

namespace PPLNAMESPACE {

Airport Airport::findInNavDatabase(const std::string& code) {
    Airport instance;
    instance.navRef_ = XPLMFindNavAid(nullptr, code.c_str(), nullptr, nullptr, nullptr, xplm_Nav_Airport);
    if(instance.navRef_ == XPLM_NAV_NOT_FOUND) {
        throw std::invalid_argument("No airport with the requested ID was found");
    }
    // Reserve space in the strings for copying the information
    instance.name_.resize(256);
    // Get information
    XPLMGetNavAidInfo(instance.navRef_, nullptr, &instance.latitude_, &instance.longitude_, &instance.elevation_, nullptr, nullptr, nullptr, &*instance.name_.begin(), nullptr);
    
    return instance;
}

std::string Airport::name() const {
    return name_;
}

std::string Airport::code() const {
    return code_;
}

float Airport::elevation() const {
    return elevation_;
}

float Airport::latitude() const {
    return latitude_;
}

float Airport::longitude() const {
    return longitude_;
}

XPLMNavRef Airport::underlyingReference() {
    if(navRef_ == XPLM_NAV_NOT_FOUND) {
        navRef_ = findNavRef();
        if(navRef_ == XPLM_NAV_NOT_FOUND) {
            throw new std::runtime_error("No navaid with this airport ID found by X-Plane");
        }
    }
    return navRef_;
}

XPLMNavRef Airport::findNavRef() {
    return XPLMFindNavAid(nullptr, code_.c_str(), nullptr, nullptr, nullptr, xplm_Nav_Airport);
}

}
