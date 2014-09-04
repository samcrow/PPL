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

#ifndef AIRPORTCACHE_H
#define AIRPORTCACHE_H

#include "../../namespaces.h"
#include "../../util/concurrentmap.h"
#include "../exceptions.h"
#include <fstream>
#include <unordered_map>
#include <future>
#include "aptdatreader.h"

namespace PPLNAMESPACE {
namespace detail {

/**
 * @brief The AptDatCache class provides access to
 * cached information on airports from an apt.dat file.
 * 
 * Instead of actually caching airport information in memory,
 * this class stores the position in the apt.dat file where each
 * airport's record begins. 
 */
class AptDatCache
{
public:
    /**
     * @brief Constructor
     * @param path The path to the apt.dat file
     */
    AptDatCache(const std::string& path);
    
    /**
     * @brief Returns the position of the entry in the apt.dat file
     * for the airport with the requested code.
     * 
     * Timing information: Before airports are cached, this method
     * searches linearly throught the apt.dat file for the requested
     * airport. This can take seconds or tens of seconds.
     * 
     * To find every airport in advance, call startFindingAllAirports().
     * 
     * @param code
     * @return The position in the file before the beginning of the airport's record
     * @throws NoSuchAirportException if no airport with the requested ID exists
     * @throws ReadInProgressException if no airport with the required ID is known
     * and it could not be searched for because a search is already in progress
     */
    std::streamsize findAirportBlocking(const std::string& code);
    
    
    std::future<std::streamsize> findAirport(const std::string& code);
    
    /**
     * @brief Returns true if the airport with the provided code
     * is cached and easily accessible. Otherwise returns false.
     * @param code
     * @return 
     */
    bool hasAirportCached(const std::string& code);
    
    /**
     * @brief Starts a procedure to asynchronously search through
     * the file and find the airport with the requested code.
     * 
     * If the requested airport is already cached, this method
     * does nothing.
     * 
     * @param code The airport code to search for
     * @throws ReadInProgressException if an airport data search is
     * already taking place
     */
    void startFindingAirport(const std::string& code);
    
    /**
     * @brief Starts a procedure to asynchronously search through
     * the file and cache the locations of all airports.
     * @throws ReadInProgressException if an airport data search
     * is already taking place
     */
    void startFindingAllAirports();
    
    /**
     * @brief Returns the path to the apt.dat file that is being used
     * @return 
     */
    std::string path() const;
    
private:
    
    AptDatReader reader;
    
    /// Maps airport IDs to file positions
    ConcurrentMap<std::string, std::streamsize> airportCache;
    /// Maps airport IDs to promises to return file positions.
    /// The code that reads the file will delete this promise
    /// after it is fulfilled.
    ConcurrentMap<std::string, std::promise<std::streamsize> * > promises;
    
    void findAllAirports();
    void findAirport_private(std::string code);
};

}
}
#endif // AIRPORTCACHE_H
