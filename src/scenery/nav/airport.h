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
#include "../../namespaces.h"
#include <string>

namespace PPLNAMESPACE {


/**
 * @brief Represents an airport from X-Plane's airport data
 */
class Airport
{
public:
    
    /**
     * @brief Finds an airport in X-Plane's in-memory copy
     * of the database using the functionality in XPLMNavigation.
     * 
     * This is generally faster than parsing the apt.dat file.
     * 
     * @param id
     * @return 
     */
    static Airport findInNavDatabase(const std::string& code);
    
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
    
    /**
     * @brief Returns the airport's latitude
     * @return 
     */
    float latitude() const;
    /**
     * @brief Returns the airport's longitude
     * @return 
     */
    float longitude() const;
    
protected:
    
    /**
     * @brief Returns the reference to X-Plane's entry for this airport.
     * 
     * If a reference is not yet known, it is created. If it could not be created,
     * an exception is thrown.
     * 
     * @return 
     */
    XPLMNavRef underlyingReference();
    
private:
    std::string name_;
    std::string code_;
    float elevation_;
    float latitude_;
    float longitude_;
    
    /**
     * @brief The reference to X-Plane's entry for this airport
     */
    XPLMNavRef navRef_ = XPLM_NAV_NOT_FOUND;
    
    XPLMNavRef findNavRef();
};

}
#endif // AIRPORT_H
