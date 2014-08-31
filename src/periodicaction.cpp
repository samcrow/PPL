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

#include "periodicaction.h"
#include <stdexcept>

namespace PPLNAMESPACE {

PeriodicAction::PeriodicAction()
{
}

PeriodicAction::PeriodicAction(periodic_function fn) :
    fn(fn)
{
    
}

void PeriodicAction::setFunction(periodic_function newFunction) {
    fn = newFunction;
}

void PeriodicAction::schedule(float periodSeconds) {
    period = periodSeconds;
    
    // Check that a flight loop is not currently active
    if(loopId != 0) {
        throw std::logic_error("A PeriodicAction that has been scheduled cannot be scheduled again until after it is cancelled");
    }
    // Check that a function has already been set
    if(!fn) {
        throw std::logic_error("A PeriodicAction must have a function set up before it can be scheduled");
    }
    
    // Create a flight loop and register it to be called after the required time
    XPLMCreateFlightLoop_t params;
    params.structSize = sizeof(XPLMCreateFlightLoop_t);
    params.phase = xplm_FlightLoop_Phase_BeforeFlightModel;
    params.callbackFunc = &PeriodicAction::callback;
    params.refcon = this;
    
    loopId = XPLMCreateFlightLoop(&params);
    // Schedule the loop to be called after the specified time
    // The third parameter is inRelativeToNow = true
    XPLMScheduleFlightLoop(loopId, periodSeconds, true);
}

void PeriodicAction::cancel() {
    if(loopId != 0) {
        XPLMDestroyFlightLoop(loopId);
        loopId = 0;
    }
}

float PeriodicAction::callback(float, float, int, void *inRefCon) {
    PeriodicAction* action = static_cast<PeriodicAction*>(inRefCon);
    // Call the function
    action->fn();
    
    // Ask to be called again after the set period
    return action->period;
}

}
