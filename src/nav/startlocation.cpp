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

#include "startlocation.h"

namespace PPLNAMESPACE {

StartLocation::StartLocation() :
    // Defaults
    heading_(0),
    type_(Type::Miscellaneous),
    // Not suitable for any aircraft
    types_({ false, false, false, false, false })
{
}

const std::string& StartLocation::name() const {
    return name_;
}
void StartLocation::setName(const std::string& newName) {
    name_ = newName;
}
void StartLocation::setName(std::string&& newName) {
    name_ = newName;
}

double StartLocation::heading() const {
    return heading_;
}
void StartLocation::setHeading(double newHeading) {
    heading_ = newHeading;
}
StartLocation::Type StartLocation::type() const {
    return type_;
}
void StartLocation::setType(Type newType) {
    type_ = newType;
}

const StartLocation::AircraftTypes& StartLocation::aircraftTypes() const {
    return types_;
}
void StartLocation::setAircraftTypes(const AircraftTypes& newTypes) {
    types_ = newTypes;
}
void StartLocation::setAircraftTypes(AircraftTypes&& newTypes) {
    types_ = newTypes;
}

StartLocation::Type StartLocation::stringToType(const std::string& string) {
    if(string == "gate") {
        return Type::Gate;
    }
    if(string == "hangar") {
        return Type::Hangar;
    }
    if(string == "misc") {
        return Type::Miscellaneous;
    }
    if(string == "tie-down") {
        return Type::TieDown;
    }
    throw std::out_of_range("No type for the provided string");
}

}
