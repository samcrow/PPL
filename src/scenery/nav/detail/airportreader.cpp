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

#include "airportreader.h"

namespace PPLNAMESPACE {
namespace detail {

AirportReader::AirportReader(const std::string& filePath, std::fstream::pos_type position) :
    stream(filePath, std::ios::in)
{
    // Move to the start position
    stream.seekg(position);
}

float AirportReader::elevation() {
    if(!elevation_.known()) {
        readFirstLine();
    }
    return elevation_.value();
}

std::string AirportReader::code() {
    if(!code_.known()) {
        readFirstLine();
    }
    return code_.value();
}

std::string AirportReader::name() {
    if(!name_.known()) {
        readFirstLine();
    }
    return name_.value();
}

AirportReader::AirportType AirportReader::type() {
    if(!type_.known()) {
        readFirstLine();
    }
    return type_.value();
}

void AirportReader::readFirstLine() {
    // Type
    std::underlying_type<AirportType>::type airportType;
    stream >> airportType;
    type_ = static_cast< AirportType >(airportType);
    
    // Elevation
    stream >> elevation_;
    // Two depreciated values
    int dummy;
    stream >> dummy;
    stream >> dummy;
    //Name: Rest of line
    std::string name;
    // Read
    while(!stream.eof()) {
        const char c = stream.get();
        if(c == '\n') {
            break;
        }
        name.push_back(c);
    }
    name_ = name;
}

}
}
