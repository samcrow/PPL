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

#ifndef AIRPORTREADER_H
#define AIRPORTREADER_H
#include "../../../namespaces.h"
#include "../../../util/uncertain.h"
#include "../runway.h"
#include "../airportfrequency.h"
#include <fstream>
#include <vector>

namespace PPLNAMESPACE {
namespace detail {

/**
 * @brief The AirportReader class reads airport information from an apt.dat file
 */
class AirportReader
{
public:
    
    typedef std::vector< Runway > runway_list_type;
    typedef std::vector< AirportFrequency > frequency_list_type;
    
    enum class AirportType {
        LandAirport = 1,
        SeaplaneBase = 16,
        Heliport = 17,
    };
    
    /**
     * @brief Constructor
     * @param filePath The path to find the apt.dat file at
     * @param position The position in the file to start at. This should be the position
     * so that the first read operation from this position will return the airport row code
     * (1, 16, or 17)
     */
    AirportReader(const std::string& filePath, std::fstream::pos_type position);
    
    float elevation();
    std::string code();
    std::string name();
    AirportType type();
    
    /**
     * @brief Returns a reference to a list of runways at this airport.
     * This list does not include water runways or helipads.
     * @return 
     */
    const runway_list_type& runways();
    
    /**
     * @brief Returns a reference to a list of radio frequencies associated
     * with this airport
     * @return 
     */
    const frequency_list_type& frequencies();
    
private:
    
    /// Position in the file of the beginning of the airport record
    std::streampos beginning;
    std::ifstream stream;
    
    /// Airport elevation, feet
    uncertain<float> elevation_;
    /// Airport code
    uncertain<std::string> code_;
    /// Airport name
    uncertain<std::string> name_;
    /// Airport type
    uncertain<AirportType> type_;
    
    /// Runways
    uncertain< runway_list_type > runways_;
    
    /// Frequencies
    uncertain< frequency_list_type> frequencies_;
    
    void readFirstLine();
    
    void readRunways();
    
    void readFrequencies();
    
    void moveToBeginning();
    
    void skipLine();
};


}
}
#endif // AIRPORTREADER_H
