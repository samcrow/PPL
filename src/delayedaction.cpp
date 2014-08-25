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

#include "delayedaction.h"
#include <stdexcept>

namespace PPLNAMESPACE {



void DelayedAction::schedule(float timeSeconds, delayed_function fn) {
    
    // Allocate the action on the heap
    DelayedAction* action = new DelayedAction();
    // Create a function that will delete the newly allocated object when it times out
    auto deletingFunction = [fn, action] () {
        fn();
        delete action;
    };
    action->setFunction(deletingFunction);
    action->schedule(timeSeconds);
    // The object will be deleted after it times out
}

DelayedAction::DelayedAction() {
    
}

DelayedAction::DelayedAction(delayed_function fn) :
    fn(fn)

{
    
}

void DelayedAction::cancel() {
    if(loopId != 0) {
        XPLMDestroyFlightLoop(loopId);
        loopId = 0;
    }
}

void DelayedAction::setFunction(delayed_function newFunction) {
    fn = newFunction;
}

void DelayedAction::schedule(float timeSeconds) {
    
    // Check that a function has already been set
    if(!fn) {
        throw std::logic_error("A DelayedAction must have a function set up before it can be scheduled");
    }
    
    // Create a flight loop and register it to be called after the required time
    XPLMCreateFlightLoop_t params;
    params.structSize = sizeof(XPLMCreateFlightLoop_t);
    params.phase = xplm_FlightLoop_Phase_BeforeFlightModel;
    params.callbackFunc = &DelayedAction::callback;
    params.refcon = this;
    
    loopId = XPLMCreateFlightLoop(&params);
    // Schedule the loop to be called after the specified time
    // The third parameter is inRelativeToNow = true
    XPLMScheduleFlightLoop(loopId, timeSeconds, true);
}

float DelayedAction::callback(float, float, int, void* inRefCon) {
    DelayedAction* action = static_cast<DelayedAction*>(inRefCon);
    // Call the function
    action->fn();
    
    // Delete the flight loop
    XPLMDestroyFlightLoop(action->loopId);
    // Mark the object as not having an active flight loop
    action->loopId = 0;
    
    // Don't get called again
    return 0;
}

}
