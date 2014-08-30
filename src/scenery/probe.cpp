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

#include "probe.h"
#include <stdexcept>
#include <XPLMGraphics.h>

namespace PPLNAMESPACE {

Probe::Probe()
{
    XPLMCreateProbe(xplm_ProbeY);
}

void Probe::probeTerrain(float x, float y, float z, ProbeResult& result) {
    XPLMProbeInfo_t info;
    info.structSize = sizeof(XPLMProbeInfo_t);
    XPLMProbeResult status = XPLMProbeTerrainXYZ(probeRef, x, y, z, &info);
    
    if(status == xplm_ProbeHitTerrain) {
        result = info;
    }
    else if(status == xplm_ProbeError) {
        throw std::runtime_error("Probe error");
    }
    else if(status == xplm_ProbeMissed) {
        // Set invalid
        result = ProbeResult();
    }
    
}

void Probe::probeTerrain(double latitude, double longitude, ProbeResult &result) {
    double xLocal;
    double yLocal;
    double zLocal;
    
    // TODO: Figure out what works for this
    const double altitudeMeters = 0;
    
    XPLMWorldToLocal(latitude, longitude, altitudeMeters, &xLocal, &yLocal, &zLocal);
    
    probeTerrain(xLocal, yLocal, zLocal, result);
}

Probe::~Probe() {
    XPLMDestroyProbe(probeRef);
}

}
