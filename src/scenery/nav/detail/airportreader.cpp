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
#include <cassert>
#include <cctype>

namespace PPLNAMESPACE {
namespace detail {

AirportReader::AirportReader(const std::string& filePath, std::fstream::pos_type position) :
    beginning(position),
    stream(filePath, std::ios::in)
{
    // Move to the start position
    stream.seekg(position);
}

float AirportReader::elevation() {
    if(!elevation_.known()) {
        readFirstLine();
        assert(elevation_.known());
    }
    return elevation_.value();
}

std::string AirportReader::code() {
    if(!code_.known()) {
        readFirstLine();
        assert(code_.known());
    }
    return code_.value();
}

std::string AirportReader::name() {
    if(!name_.known()) {
        readFirstLine();
        assert(name_.known());
    }
    return name_.value();
}

AirportReader::AirportType AirportReader::type() {
    if(!type_.known()) {
        readFirstLine();
        assert(type_.known());
    }
    return type_.value();
}

const AirportReader::runway_list_type& AirportReader::runways() {
    if(!runways_.known()) {
        readRunways();
        assert(runways_.known());
    }
    return runways_.value();
}

const AirportReader::frequency_list_type& AirportReader::frequencies() {
    if(!frequencies_.known()) {
        readFrequencies();
        assert(frequencies_.known());
    }
    return frequencies_.value();
}

void AirportReader::readFirstLine() {
    moveToBeginning();
    // Type
    std::underlying_type<AirportType>::type airportType;
    stream >> airportType;
    type_ = static_cast< AirportType >(airportType);
    
    // Elevation
    stream >> elevation_.value();
    elevation_.affirm();
    // Two depreciated values
    int dummy;
    stream >> dummy;
    stream >> dummy;
    // code
    stream >> code_.value();
    code_.affirm();
    
    // Skip spaces
    stream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    //Name: Rest of line
    // Read
    const auto readMoreLineTerminators = [this] {
        while(!stream.eof()) {
            char c = stream.peek();
            if(c == '\n' || c == '\r') {
                // Read and ignore that character
                stream.get();
            }
            else {
                break;
            }
        }
    };
    while(!stream.eof()) {
        const char c = stream.get();
        if(c == '\n' || c == '\r') {
            readMoreLineTerminators();
            break;
        }
        name_.value().push_back(c);
    }
    name_.affirm();
}

void AirportReader::readRunways() {
    moveToBeginning();
    runways_.affirm();
    
    // Skip past the first line, containing the airport code
    int dummy;
    stream >> dummy;
    skipLine();
    
    while(!stream.eof()) {
        
        // Read a line code
        
        int lineCode;
        stream >> lineCode;
        
        if(lineCode == 1 || lineCode == 16 || lineCode == 17 || stream.eof()) {
            // Got to the next airport or the end of the file
            return;
        }
        if(lineCode == 100) {
            // A runway
            Runway runway;
            
            // iter now points to the new Runway object
            float width;
            stream >> width;
            runway.setWidth(width);
            
            std::underlying_type<Runway::Surface>::type surface;
            stream >> surface;
            runway.setSurface(static_cast<Runway::Surface>(surface));
            
            std::underlying_type<Runway::Shoulder>::type shoulder;
            stream >> shoulder;
            runway.setShoulder(static_cast<Runway::Shoulder>(shoulder));
            
            float roughness;
            stream >> roughness;
            runway.setRoughness(roughness);
            
            bool centerlineLights;
            stream >> centerlineLights;
            runway.setHasCenterlineLights(centerlineLights);
            
            std::underlying_type<Runway::EdgeLights>::type edgeLights;
            stream >> edgeLights;
            runway.setEdgeLights(static_cast<Runway::EdgeLights>(edgeLights));
            
            bool distanceSigns;
            stream >> distanceSigns;
            runway.setHasGeneratedDistanceSigns(distanceSigns);
            
            auto parseEnd = [this, &runway](Runway::End& end) {
                std::string name;
                stream >> name;
                // Switch based on the last character of the name
                switch(name.back()) {
                case 'L':
                    end.setSuffix(Runway::End::Suffix::L);
                    break;
                case 'C':
                    end.setSuffix(Runway::End::Suffix::C);
                    break;
                case 'R':
                    end.setSuffix(Runway::End::Suffix::R);
                    break;
                default:
                    end.setSuffix(Runway::End::Suffix::None);
                }
                // Extract heading
                if(std::isdigit(name.back())) {
                    // Expect that the whole name is the heeading
                    end.setHeading(std::stoi(name));
                }
                else {
                    // Get the heading from the characters of the
                    // name before the suffix
                    name.resize(name.size() - 1);
                    end.setHeading(std::stoi(name));
                }
                
                double latitude;
                stream >> latitude;
                end.setLatitude(latitude);
                double longitude;
                stream >> longitude;
                end.setLongitude(longitude);
                
                float displacedThreshold;
                stream >> displacedThreshold;
                end.setDisplacedThresholdLength(displacedThreshold);
                float blastpad;
                stream >> blastpad;
                end.setBlastPadLength(blastpad);
                
                std::underlying_type<Runway::Markings>::type markings;
                stream >> markings;
                // Set the markings property of the runway
                runway.setMarkings(static_cast<Runway::Markings>(markings));
                
                std::underlying_type<Runway::End::ApproachLighting>::type approachLighting;
                stream >> approachLighting;
                end.setApproachLighting(static_cast<Runway::End::ApproachLighting>(approachLighting));
                
                bool touchdownZoneLighting;
                stream >> touchdownZoneLighting;
                end.setTouchdownZoneLighting(touchdownZoneLighting);
                
                std::underlying_type<Runway::End::RunwayEndIdentifierLights>::type reil;
                stream >> reil;
                end.setRunwayEndIdentifierLights(static_cast<Runway::End::RunwayEndIdentifierLights>(reil));
                
            };
            
            // End 1
            Runway::End end1;
            parseEnd(end1);
            runway.setEnd1(end1);
            // End 2
            Runway::End end2;
            parseEnd(end2);
            runway.setEnd2(end2);
            
            // Add runway to the list
            runways_.value().push_back(runway);
            // Done
            skipLine();
        }
        else {
            // Something other than a runway
            skipLine();
            continue;
        }
        
    }
    
}

void AirportReader::readFrequencies() {
    moveToBeginning();
    frequencies_.affirm();
    
    // Skip past the first line, containing the airport code
    int dummy;
    stream >> dummy;
    skipLine();
    
    while(!stream.eof()) {
        // Read a line code
        
        int lineCode;
        stream >> lineCode;

        if(lineCode == 1 || lineCode == 16 || lineCode == 17 || stream.eof()) {
            // Got to the next airport or the end of the file
            return;
        }
        if(lineCode == AirportFrequency::Type::Recorded || lineCode == AirportFrequency::Type::Unicom
                || lineCode == AirportFrequency::Type::ClearanceDelivery || lineCode == AirportFrequency::Type::Ground
                || lineCode == AirportFrequency::Type::Tower || lineCode == AirportFrequency::Type::Departure)
        {
            // Create and assign a frequency
            
            AirportFrequency::hertz_type hundredsOfMegahertz;
            stream >> hundredsOfMegahertz;
            
            // Skip whitespace
            while(!stream.eof()) {
                const char c = stream.peek();
                if(std::isblank(c)) {
                    // Read and ignore this character
                    stream.get();
                }
                else {
                    // Moved beyond whitespace
                    break;
                }
            }
            // Read the rest of the line for the name
            std::string name;
            while(!stream.eof()) {
                const char c = stream.get();
                if(c == '\r' || c == '\n') {
                    break;
                }
                name.append({ c });
            }
            // Read any more line separators that may exist
            while(!stream.eof()) {
                char c = stream.peek();
                if(c == '\r' || c == '\n') {
                    stream.get();
                }
                else {
                    break;
                }
            }
            
            AirportFrequency frequency(hundredsOfMegahertz * 10000, static_cast<AirportFrequency::Type>(lineCode), name);
            frequencies_.value().push_back(frequency);
        }
        else {
            // Something other than a runway
            skipLine();
            continue;
        }
    }
}

void AirportReader::moveToBeginning() {
    stream.clear();
    stream.seekg(beginning);
}

void AirportReader::skipLine() {
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

}
}
