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
#include <iostream>
#include "../pluginpath.h"
#include "detail/airportreader.h"

namespace PPLNAMESPACE {

std::unique_ptr<detail::AptDatCache> Airport::cache_;

Airport::Airport(const std::string& code) :
    code_(code)
{
    navRef_ = findNavRef();
    if(navRef_ == XPLM_NAV_NOT_FOUND) {
        throw std::invalid_argument("No airport with the requested ID was found");
    }
    // Reserve space
    name_.resize(256);
    float latitude;
    float longitude;
    
    XPLMGetNavAidInfo(navRef_, nullptr, &latitude, &longitude, &elevation_, nullptr, nullptr, nullptr, &name_.front(), nullptr);
    setPosition({ latitude, longitude });
    
    // Start the apt.dat reading, if not already started
    try {
        if(!cache().hasAirportCached(code_)) {
            cache().startFindingAllAirports();
        }
    }
    catch (std::exception& ex) { std::cerr << "Failed to start finding all airports: " << ex.what() << std::endl; }
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

bool Airport::hasRunways() {
    if(!runways_) {
        // Check
        if(cache().hasAirportCached(code_)) {
            copyDataFromCache();
        }
    }
    return runways_.operator bool();
}

bool Airport::hasHelipads() {
    if(!helipads_) {
        // Check
        if(cache().hasAirportCached(code_)) {
            copyDataFromCache();
        }
    }
    return helipads_.operator bool();
}

bool Airport::hasFrequencies() {
    if(!frequencies_) {
        // Check
        if(cache().hasAirportCached(code_)) {
            copyDataFromCache();
        }
    }
    return frequencies_.operator bool();
}

bool Airport::hasStartLocations() {
    if(!startLocations_) {
        // Check
        if(cache().hasAirportCached(code_)) {
            copyDataFromCache();
        }
    }
    return frequencies_.operator bool();
}

bool Airport::hasType() {
    if(!type_) {
        // Check
        if(cache().hasAirportCached(code_)) {
            copyDataFromCache();
        }
    }
    return type_.operator bool();
}

const Airport::runway_list_type& Airport::runways() {
    if(!hasRunways()) {
        throw std::runtime_error("runways() cannot be called when hasRunways() has returned false");
    }
    return runways_.value();
}

const Airport::helipad_list_type& Airport::helipads() {
    if(!hasHelipads()) {
        throw std::runtime_error("helipads() cannot be called when hasHelipads() has returned false");
    }
    return helipads_.value();
}

const Airport::frequency_list_type& Airport::frequencies() {
    if(!hasFrequencies()) {
        throw std::runtime_error("frequencies() cannot be called when hasFrequencies() has returned false");
    }
    return frequencies_.value();
}

const Airport::start_location_list_type& Airport::startLocations() {
    if(!hasStartLocations()) {
        throw std::runtime_error("startLocations() cannot be called when hasStartLocations() has returned false");
    }
    return startLocations_.value();
}

Airport::Type Airport::type() {
    if(!hasType()) {
        throw std::runtime_error("type() cannot be called when hasType() has returned false");
    }
    return type_.value();
}

XPLMNavRef Airport::underlyingReference() {
    if(navRef_ == XPLM_NAV_NOT_FOUND) {
        navRef_ = findNavRef();
        if(navRef_ == XPLM_NAV_NOT_FOUND) {
            throw std::runtime_error("No navaid with this airport ID found by X-Plane");
        }
    }
    return navRef_;
}

XPLMNavRef Airport::findNavRef() {
    return XPLMFindNavAid(nullptr, code_.c_str(), nullptr, nullptr, nullptr, xplm_Nav_Airport);
}


detail::AptDatCache& Airport::cache() {
    if(!cache_) {
        cache_.reset(new detail::AptDatCache(PluginPath::prependXPlanePath("/Resources/default scenery/default apt dat/Earth nav data/apt.dat")));
    }
    return *cache_;
}

void Airport::copyDataFromCache() {
    detail::AirportReader reader(cache().path(), cache().findAirport(code_));
    runways_ = reader.runways();
    helipads_ = reader.helipads();
    frequencies_ = reader.frequencies();
    startLocations_ = reader.startLocations();
    switch(reader.type()) {
    case detail::AirportReader::AirportType::LandAirport:
        type_ = Type::Airport;
        break;
    case detail::AirportReader::AirportType::SeaplaneBase:
        type_ = Type::SeaplaneBase;
        break;
    case detail::AirportReader::AirportType::Heliport:
        type_ = Type::Heliport;
        break;
    }
}

}
