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

#ifndef AIRPORTFREQUENCY_H
#define AIRPORTFREQUENCY_H

#include "../namespaces.h"
#include "frequency.h"
#include <ostream>

namespace PPLNAMESPACE {

/**
 * @brief A type of frequency that includes a name and a type identifying its
 * use at an airport
 */
class AirportFrequency : public Frequency
{
public:
    
    // Types of frequencies
    enum Type {
        Recorded = 50,
        Unicom = 51,
        ClearanceDelivery = 52,
        Ground = 53,
        Tower = 54,
        Approach = 56,
        Departure = 57,
    };
    
    /**
     * @brief Default constructor.
     * 
     * The frequency will be set to zero.
     */
    AirportFrequency(Type type);
    
    AirportFrequency(hertz_type hertz, Type type);
    
    AirportFrequency(float megahertz, Type type);
    
    AirportFrequency(hertz_type hertz, Type type, const std::string& name = std::string());
    
    AirportFrequency(float megahertz, Type type, const std::string& name = std::string());
    
    /**
     * @brief Parses a string representation of a number of megahertz
     * @param megahertz
     */
    AirportFrequency(const std::string& megahertz, Type type, const std::string& name = std::string());
    
    Type type() const;
    std::string name() const;
    
    void setType(Type newType);
    void setName(const std::string& newName);
    
    friend std::ostream& operator << (std::ostream& stream, const AirportFrequency& frequency);
    
private:
    
    Type type_;
    std::string name_;
    
};

}

#endif // AIRPORTFREQUENCY_H
