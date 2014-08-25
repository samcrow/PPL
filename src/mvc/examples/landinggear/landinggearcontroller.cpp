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

#include "landinggearcontroller.h"
#include "landinggearmodelxplane.h"
#include <cmath>
#include <iostream>

namespace PPLNAMESPACE {


LandingGearController::LandingGearController(LandingGearModel &model) :
    Controller("Landing gear", model),
    PPL::Processor(),
    lastDeployRatio(NAN)
{
}

void LandingGearController::retract() {
    model().setExtended(false);
}

void LandingGearController::deploy() {
    model().setExtended(true);
}

boost::signals2::connection LandingGearController::addExtendFinishedListener(const listener_type& listener) {
    return extendedSignal.connect(listener);
}
boost::signals2::connection LandingGearController::addRetractFinishedListener(const listener_type& listener) {
    return retractedSignal.connect(listener);
}
boost::signals2::connection LandingGearController::addExtendStartedListener(const listener_type &listener) {
    return extensionStartedSignal.connect(listener);
}
boost::signals2::connection LandingGearController::addRetractStartedListener(const listener_type &listener) {
    return retractionStartedSignal.connect(listener);
}

LandingGearController::~LandingGearController() {
    
}


// Flight loop callback
float LandingGearController::callback(float, float, int)
{
    
    // Get deploy ratio from the model
    float deployRatio = model().deployRatio();
    
    // See if deploy ratio has changed
    if(std::isnan(lastDeployRatio)) {
        // Deploy ratio not yet set. Don't do any of the following conditions
    }
    else if(isBasicallyOne(deployRatio) && !isBasicallyOne(lastDeployRatio)) {
        // Just finished deploying
        extendedSignal();
    }
    else if(isBasicallyZero(deployRatio) && !isBasicallyZero(lastDeployRatio)) {
        // Just finished retracting
        retractedSignal();
    }
    else if(!isBasicallyZero(deployRatio) && isBasicallyZero(lastDeployRatio)) {
        // Just started extending
        extensionStartedSignal();
    }
    else if(!isBasicallyOne(deployRatio) && isBasicallyOne(lastDeployRatio)) {
        // Just started retracting
        retractionStartedSignal();
    }
    
    lastDeployRatio = deployRatio;
    
    return -1;
}

bool LandingGearController::isBasicallyOne(float value) {
    return value > 0.999999f;
}

bool LandingGearController::isBasicallyZero(float value) {
    return value < 0.0000001f;
}

}
