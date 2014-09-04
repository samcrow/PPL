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

#include "frequency.h"
#include <boost/lexical_cast.hpp>
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace PPLNAMESPACE {

Frequency::Frequency(const std::string& megahertz) :
    hertz_( boost::lexical_cast<float>(megahertz) * 1000000 )
{  
}

Frequency::hertz_type Frequency::hertz() const {
    return hertz_;
}

Frequency::hertz_type Frequency::ten_hertz() const {
    return hertz_ / 10;
}

float Frequency::megahertz() const {
    return float(hertz_) / 1000000;
}

float Frequency::kilohertz() const {
    return float(hertz_) / 1000;
}

std::string Frequency::toMhzString() const {
    std::stringstream stream;
    
    int megahertz = hertz_ / 1000000;
    int otherDigits = (hertz_ % 1000000) / 10000;
    
    stream << std::setfill('0') << std::setw(3);
    stream << megahertz;
    stream << '.';
    stream << std::setw(2);
    stream << otherDigits;
    
    
    return stream.str();
}

Frequency Frequency::operator + (const Frequency& other) const {
    return Frequency(this->hertz() + other.hertz());
}

Frequency Frequency::operator - (const Frequency& other) const {
    // Check non-negative result
    if(other.hertz() > this->hertz()) {
        throw std::underflow_error("Frequency: Performing this frequency subtraction would create a negative frequency");
    }
    
    return Frequency(this->hertz() - other.hertz());
}

void Frequency::operator -= (const Frequency& other) {
    // Check non-negative result
    if(other.hertz() > this->hertz()) {
        throw std::underflow_error("Frequency: Performing this frequency subtraction would create a negative frequency");
    }
    
    hertz_ -= other.hertz();
}

void Frequency::operator += (const Frequency& other) {
    hertz_ += other.hertz();
}

Frequency Frequency::operator - () const {
    return Frequency(-hertz_);
}

std::ostream& operator << (std::ostream& stream, const Frequency& freq) {
    stream << "Frequency[ " << freq.megahertz() << " MHz]";
    return stream;
}

}
