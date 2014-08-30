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

#include "proberesult.h"

namespace PPLNAMESPACE {

ProbeResult::ProbeResult() :
    valid_(false)
{
    
}

float ProbeResult::x() const {
    return x_;
}
float ProbeResult::y() const {
    return y_;
}
float ProbeResult::z() const {
    return z_;
}

float ProbeResult::normalX() const {
    return normalX_;
}
float ProbeResult::normalY() const {
    return normalY_;
}
float ProbeResult::normalZ() const {
    return normalZ_;
}

float ProbeResult::velocityX() const {
    return velocityX_;
}
float ProbeResult::velocityY() const {
    return velocityY_;
}
float ProbeResult::velocityZ() const {
    return velocityZ_;
}

bool ProbeResult::isWater() const {
    return water;
}

ProbeResult::ProbeResult(const XPLMProbeInfo_t& info) :
    x_(info.locationX),
    y_(info.locationY),
    z_(info.locationZ),
    
    normalX_(info.normalX),
    normalY_(info.normalY),
    normalZ_(info.normalZ),
    
    velocityX_(info.velocityX),
    velocityY_(info.velocityY),
    velocityZ_(info.velocityY),
    
    water(info.is_wet),
    
    valid_(true)
{
    
}

void ProbeResult::operator = (const XPLMProbeInfo_t& info) {
    x_ = info.locationX;
    y_ = info.locationY;
    z_ = info.locationZ;
    
    normalX_ = info.normalX;
    normalY_ = info.normalY;
    normalZ_ = info.normalZ;
    
    velocityX_ = info.velocityX;
    velocityY_ = info.velocityY;
    velocityZ_ = info.velocityZ;
    
    water = info.is_wet;
    
    valid_ = true;
}

bool ProbeResult::isValid() const {
    return valid_;
}

}
