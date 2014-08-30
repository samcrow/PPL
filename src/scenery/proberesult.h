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

#ifndef PROBERESULT_H
#define PROBERESULT_H
#include "../namespaces.h"
#include <XPLMScenery.h>

namespace PPLNAMESPACE {

/**
 * @brief The ProbeResult class provides information
 * that is accesed by a {@link Probe}
 */
class ProbeResult
{
public:
    
    /**
     * @brief Creates an invalid result
     */
    ProbeResult();
    
    bool isValid() const;
    
    float x() const;
    float y() const;
    float z() const;
    
    float normalX() const;
    float normalY() const;
    float normalZ() const;
    
    float velocityX() const;
    float velocityY() const;
    float velocityZ() const;
    
    bool isWater() const;
    
protected:
    friend class Probe;
    
    /**
     * @brief Creates a result based on the provided probe information
     * @param info
     */
    ProbeResult(const XPLMProbeInfo_t& info);
    
    /**
     * @brief Sets the properties of this object based on the 
     * provided probe information
     * @param info
     */
    void operator = (const XPLMProbeInfo_t& info);
    
    float x_;
    float y_;
    float z_;
    
    float normalX_;
    float normalY_;
    float normalZ_;
    
    float velocityX_;
    float velocityY_;
    float velocityZ_;
    
    bool water;
    
    /**
     * @brief If this result is valid. If the probe result code
     * is xplm_ProbeMissed, an invalid ProbeResult will be created.
     */
    bool valid_;
};

}

#endif // PROBERESULT_H
