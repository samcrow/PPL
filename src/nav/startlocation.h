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

#ifndef STARTLOCATION_H
#define STARTLOCATION_H
#include "navaid.h"

namespace PPLNAMESPACE {

/// Represents a startup location at an airport
class StartLocation : public Navaid
{
public:

    /// Location types
    enum class Type {
        Gate,
        Hangar,
        Miscellaneous,
        TieDown,
    };

    /// Types of aircraft that should use this location
    struct AircraftTypes {
        /// If this location is suitable for helicopters
        bool helicopters;
        /// If this location is suitable for piston-engined propeller aircraft
        bool props;
        /// If this location is suitable for turboprop aircraft
        bool turboprops;
        /// If this location is suitable for jet aircraft
        bool jets;
        /// If this location is suitable for heavy jet aircraft
        bool heavyJets;
    };

    StartLocation();

    // Pull Navaid::setPosition in as a public function of this class
    using Navaid::setPosition;

    const std::string& name() const;
    void setName(const std::string& newName);
    void setName(std::string&& newName);
    double heading() const;
    void setHeading(double newHeading);
    Type type() const;
    void setType(Type newType);
    const AircraftTypes& aircraftTypes() const;
    void setAircraftTypes(const AircraftTypes& newTypes);
    void setAircraftTypes(AircraftTypes&& newTypes);

    /// Converts a type string to a type.
    /// @throws std::out_of_range if no matching type exists
    static Type stringToType(const std::string& string);

private:
    std::string name_;
    double heading_;
    Type type_;
    AircraftTypes types_;
};

}
#endif // STARTLOCATION_H
