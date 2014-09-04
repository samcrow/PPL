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

#include "aptdatcache.h"
#include <thread>
#include <iostream>

namespace PPLNAMESPACE {
namespace detail {

AptDatCache::AptDatCache(const std::string& path) :
    reader(path)
{
    
}

std::streamsize AptDatCache::findAirportByCode(const std::string& code) {

    try {
        return airportCache.at(code);
    }
    catch (std::out_of_range&) {
        // Not in cache
        if(reader.allAirportsRead()) {
            // Don't have anything more to read
            throw NoSuchAirportException("No airport with the requested ID was found");
        }
        else {
            // Try to read from the file
            if(reader.allAirportsRead()) {
                throw NoSuchAirportException("No airport");
            }
            if(!reader.readInProgress()) {
                reader.findAirport(airportCache, code);
                try {
                    return airportCache.at(code);
                }
                catch (std::out_of_range&) {
                    throw NoSuchAirportException("No airport, after searching");
                }
            }
            else {
                // Reading is in progress; can't start another one right now
                throw ReadInProgressException("Airport not yet found; reading still in progress");
            }
        }
    }
}

bool AptDatCache::hasAirportCached(const std::string& code) {
    return airportCache.contains(code);
}

std::string AptDatCache::path() const {
    return reader.path();
}

void AptDatCache::startFindingAirport(const std::string& code) {
    if(reader.readInProgress()) {
        throw ReadInProgressException("Reading already in progress. Can't search.");
    }
    
    std::thread findThread(&AptDatCache::findAirport_private, this, code);
    findThread.detach();
}

void AptDatCache::startFindingAllAirports() {
    if(reader.readInProgress()) {
        throw ReadInProgressException("Reading already in progress. Can't search.");
    }
    
    std::thread findThread(&AptDatCache::findAllAirports, this);
    findThread.detach();
}

void AptDatCache::findAllAirports() {    
    // Find airports; don't stop until the end
    reader.findAirportsUntil(airportCache, [](const std::string&){ return false; });
}

void AptDatCache::findAirport_private(std::string code) {
    reader.findAirportsUntil(airportCache, [&code](const std::string& foundCode) { return code == foundCode; });
}

}
}
