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

#ifndef PROBE_H
#define PROBE_H
#include "../namespaces.h"
#include "proberesult.h"
#include <XPLMScenery.h>

namespace PPLNAMESPACE {

/**
 * @brief The Probe class can be used to get information
 * on the scenery surrounding the aircraft.
 */
class Probe
{
public:
        
    Probe();
    
    /**
     * @brief Probes the terrain at the provided local coordinates
     * and sets the result object.
     * 
     * The result object is set to invalid if the probe did not succeed
     * because it did not hit terrain.
     * 
     * @param x
     * @param y
     * @param z
     * @param result
     */
    void probeTerrain(float x, float y, float z, ProbeResult& result);
    
    /**
     * @brief Probes the terrain at the provided latitude and longitude
     * and sets the result object.
     * 
     * The result object is set to invalid if the probe did not succeed
     * because it did not hit terrain.
     * f
     * @param latitude
     * @param longitude
     * @param result
     */
    void probeTerrain(double latitude, double longitude, ProbeResult& result);
    
     ~Probe();
    
private:
    XPLMProbeRef probeRef;
};

}
#endif // PROBE_H
