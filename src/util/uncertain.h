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

#ifndef UNCERTAIN_H
#define UNCERTAIN_H
#include "../namespaces.h"

namespace PPLNAMESPACE {

/**
 * Stores an object and a flag that describes whether this value is known
 */
template < typename T >
class uncertain {
public:
    /**
     * @brief Creates an unknown object
     */
    uncertain() :
        known_(false)
    {
        
    }
    /**
     * @brief Creates a known object from the provided value
     * @param value
     */
    uncertain(const T& value) :
        known_(true),
        value_(value)
    {
        
    }
    /**
     * @brief Creates a known object from the provided value
     * @param value
     */
    uncertain(T&& value) :
        known_(true),
        value_(value)
    {
        
    }
    /**
     * @brief Returns the value. The result is undefined
     * if this instance is unknown
     * @return 
     */
    const T& value() const {
        return value_;
    }
    
    /**
     * @brief Returns a non-const reference to the value
     * @return 
     */
    T& value() {
        return value_;
    }
    
    /**
     * Assigns the given value to this object
     * and makes it known
     */
    template < typename T2 >
    void operator = (T2 newValue) {
        value_ = newValue;
        known_ = true;
    }
    
    bool known() const {
        return known_;
    }
    
    /**
     * @brief Sets this object to have a known value
     */
    void affirm() {
        known_ = true;
    }
    /**
     * @brief Sets this object to have an unknown value
     */
    void question() {
        known_ = false;
    }
    
    /**
     * @brief Returns the value stored in this object
     */
    operator T() const {
        return value_;
    }
    
private:
    bool known_ = false;
    T value_;
};

}
#endif // UNCERTAIN_H
