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

#ifndef APTDATREADER_H
#define APTDATREADER_H
#include <fstream>
#include <unordered_map>
#include <functional>
#include <atomic>
#include "../../../namespaces.h"

namespace PPLNAMESPACE {
namespace detail {

/**
 * @brief The AptDatReader class parses an apt.dat file and finds the locations
 * of airports in the file
 */
class AptDatReader
{
public:
    AptDatReader(const std::string& filePath);
    
    /**
     * @brief A function called with the code of the last read airport as a parameter.
     * If the function returns true, airport processing will stop
     */
    typedef std::function< bool (const std::string&) > airport_stop_predicate;
    
    /**
     * @brief Finds an airport with the given ID and adds its
     * position to the cache. Also adds the positions of other airports
     * that are found on the way.
     * 
     * If the requested airport is not found, it is not added
     * to the cache.
     * 
     * @param code
     * @return 
     */
    template < typename Map >
    void findAirport(Map& map, const std::string& code) {
        findAirportsUntil(map, [code](const std::string& foundCode) {
            return code == foundCode;
        });
    }
    
    /**
     * Finds and caches airports into the provided map until the provided
     * predicate returns true for the last read airport code
     */
    template < typename Map >
    void findAirportsUntil(Map& map, airport_stop_predicate predicate) {
        readInProgress_.store(true);
        ensureOpen();
        moveToBeginning();
        
        // Read airports (code 1, 16, or 17)
        while(!stream.eof()) {
            const std::streamsize lineStart = stream.tellg();
            int id;
            stream >> id;
            
            if(stream.fail()){
                stream.clear();
                // Try the next line
                skipLine();
                continue;
            }
            
            // Ignore IDs that are not 1, 16, or 17
            if(!( id == 1 || id == 16 || id == 17)) {
                skipLine();
                continue;
            }
            
            // Read and ignore elevation and two depreciated values
            int dummy;
            for(int i = 0; i < 3; i++) {
                stream >> dummy;
            }
            
            std::string foundCode;
            stream >> foundCode;
            
            // Add this airport to the cache
            map.set(foundCode, lineStart);
            
            // Stop if predicate
            if(predicate(foundCode)) {
                readInProgress_.store(false);
                return;
            }
        }
        // Here means the stream is at the end of file
        allAirportsRead_ = true;
        stream.clear();
        readInProgress_.store(false);
    }
    
    
    const std::string& path() const;
    
    bool allAirportsRead() const;
    
    bool readInProgress() const;
    
private:
    const std::string filePath;
    
    std::ifstream stream;
    
    bool allAirportsRead_ = false;
    
    std::atomic_bool readInProgress_;
    
    /**
     * @brief Opens the stream if it is not open
     */
    void ensureOpen();
    
    /**
     * @brief Moves the stream to the beginning of the file,
     * and then skips two lines to get past the headers
     */
    void moveToBeginning();
    
    /**
     * @brief Reads and discards characters from the stream until \n is read,
     * then returns
     */
    void skipLine();

    std::string readLine();
};

}
}
#endif // APTDATREADER_H
