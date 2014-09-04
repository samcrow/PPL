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

#ifndef FREQUENCY_H
#define FREQUENCY_H
#include <cstdint>
#include <string>
#include "../namespaces.h"

namespace PPLNAMESPACE {

/**
 * @brief The Frequency class stores a radio frequency
 * and allows its components to be accessed.
 */
class Frequency
{
public:
    
    typedef std::int32_t hertz_type;
    
    /**
     * @brief Default constructor.
     * 
     * The frequency will be set to zero.
     */
    constexpr Frequency() :
        hertz_(0)
    {
    }
    
    constexpr Frequency(hertz_type hertz) :
        hertz_(hertz)
    {
    }
    
    constexpr Frequency(float megahertz) :
        hertz_(megahertz * 1000000)
    {
    }
    
    /**
     * @brief Parses a string representation of a number of megahertz
     * @param megahertz
     */
    Frequency(const std::string& megahertz);
    
    // Accessors
    
    /**
     * @brief Returns this frequency in hertz
     */
    hertz_type hertz() const;
    
    /**
     * @brief Returns this frequency in tens of hertz
     */
    hertz_type ten_hertz() const;
    
    /**
     * @return This frequency in megahertz
     */
    float megahertz() const;
    /**
     * @return This frequency in kilohertz
     */
    float kilohertz() const;
    
    /**
     * @brief Prints this frequency to an ostream
     * @param stream
     * @param freq
     * @return 
     */
    friend std::ostream& operator << (std::ostream& stream, const Frequency& freq);
    
    /**
     * @brief Converts this frequency into a string
     * representing this frequency in megahertz, with three digits
     * before the decimal place and two digits after the decimal place.
     * @return 
     */
    std::string toMhzString() const;
    
    // Operators
    
    /**
     * @brief Adds two frequencies
     * @param other
     * @return 
     */
    Frequency operator + (const Frequency& other) const;
    /**
     * @brief Subtracts two frequencies
     * @param other
     * @return 
     */
    Frequency operator - (const Frequency& other) const;
    
    void operator += (const Frequency& other);
    
    void operator -= (const Frequency& other);
    
    /**
     * @brief Creates a Frequency that is a negated
     * version of this frequency
     * @return 
     */
    Frequency operator - () const;
    
private:
    
    /**
     * @brief The underlying frequency, in hertz.
     */
    hertz_type hertz_;
    
};

/**
  * A literal operator that allows creating Frequency objects from
  * hertz numbers.
  * 
  * Example: Frequency nav1 = 111700000_hz
  */ 
constexpr Frequency operator "" _hz ( unsigned long long hertz ) {
    
    return Frequency( Frequency::hertz_type(hertz));
}

/**
  * A literal operator that allows creating Frequency objects from
  * numbers of kilohertz.
  * 
  * Example: Frequency nav1 = 111700_khz
  */ 
constexpr Frequency operator "" _khz (unsigned long long kilohertz ) {
    return Frequency( Frequency::hertz_type(kilohertz) * 1000  );
}

/**
  * A literal operator that allows creating Frequency objects from
  * numbers of kilohertz.
  * 
  * Example: Frequency nav1 = 111.70_khz
  */ 
constexpr Frequency operator "" _khz (long double kilohertz ) {
    return Frequency( Frequency::hertz_type( kilohertz * 1000 )  );
}

/**
  * A literal operator that allows creating Frequency objects from
  * numbers of megahertz.
  * 
  * Example: Frequency nav1 = 111.70_mhz
  */ 
constexpr Frequency operator "" _mhz (long double megahertz ) {
    return Frequency( Frequency::hertz_type( megahertz * 1000000 )  );
}

/**
  * A literal operator that allows creating Frequency objects from
  * numbers of megahertz.
  * 
  * Example: Frequency nav1 = 111_mhz
  */ 
constexpr Frequency operator "" _mhz (unsigned long long megahertz ) {
    return Frequency( Frequency::hertz_type( megahertz * 1000000 )  );
}

}

#endif // FREQUENCY_H
