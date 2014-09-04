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

#include "airportfrequency.h"

namespace PPLNAMESPACE {

AirportFrequency::AirportFrequency(Type type) :
    Frequency(),
    type_(type)
{
}

AirportFrequency::AirportFrequency(hertz_type hertz, Type type) :
    Frequency(hertz),
    type_(type)
{
}

AirportFrequency::AirportFrequency(float megahertz, Type type) :
    Frequency(megahertz),
    type_(type)
{
}

AirportFrequency::AirportFrequency(hertz_type hertz, Type type, const std::string& name) :
    Frequency(hertz),
    type_(type),
    name_(name)
{
}
AirportFrequency::AirportFrequency(float megahertz, Type type, const std::string& name) :
    Frequency(megahertz),
    type_(type),
    name_(name)
{
}
AirportFrequency::AirportFrequency(const std::string& megahertz, Type type, const std::string& name) :
    Frequency(megahertz),
    type_(type),
    name_(name)
{
}

AirportFrequency::Type AirportFrequency::type() const {
    return type_;
}

std::string AirportFrequency::name() const {
    return name_;
}

void AirportFrequency::setType(Type newType) {
    type_ = newType;
}

void AirportFrequency::setName(const std::string &newName) {
    name_ = newName;
}

std::ostream& operator << (std::ostream& stream, const AirportFrequency& frequency) {
    stream << "Frequency " << frequency.toMhzString() << ", type " << frequency.type() << ": " << frequency.name();
    return stream;
}

}
