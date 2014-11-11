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

#ifndef AIRPORT_H
#define AIRPORT_H
#include <XPLMNavigation.h>
#include "navaid.h"
#include "helipad.h"
#include "runway.h"
#include "airportfrequency.h"
#include "startlocation.h"
#include "detail/aptdatcache.h"
#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <future>

namespace PPLNAMESPACE {


/**
 * @brief Represents an airport from X-Plane's airport data
 */
class Airport : public Navaid
{
public:
    
    enum class Type {
        Airport,
        SeaplaneBase,
        Heliport,
    };
    
    typedef std::vector<Runway> runway_list_type;
    typedef std::vector<Helipad> helipad_list_type;
    typedef std::vector<AirportFrequency> frequency_list_type;
    typedef std::vector<StartLocation> start_location_list_type;
    
    Airport(const std::string& code);
    
    /**
     * @brief Returns the name of this airport
     * @return 
     */
    std::string name() const;
    /**
     * @brief Returns the ICAO/FAA code of the airport
     * @return 
     */
    std::string code() const;
    
    /**
     * @brief Returns the elevation of the airport in feet
     * @return 
     */
    float elevation() const;
    
    // Next: Accessors for information from the airport data file
    
    bool hasRunways();
    const runway_list_type& runways();

    bool hasHelipads();
    const helipad_list_type& helipads();
    
    bool hasFrequencies();
    const frequency_list_type& frequencies();

    bool hasStartLocations();
    const start_location_list_type& startLocations();
    
    bool hasType();
    Type type();
    
protected:

    
private:
    
    boost::optional<runway_list_type> runways_;
    boost::optional<helipad_list_type> helipads_;
    boost::optional<frequency_list_type> frequencies_;
    boost::optional<start_location_list_type> startLocations_;
    boost::optional<Type> type_;

    
    static XPLMNavRef findNavRef(const std::string& code);
    
    void copyDataFromCache();
    
    // Data cache operations
    static std::unique_ptr<detail::AptDatCache> cache_;
    
    /// Returns a cache used to access more advanced airport
    /// information. If the cache does not exist, creates it.
    static detail::AptDatCache& cache();
};

}
#endif // AIRPORT_H
