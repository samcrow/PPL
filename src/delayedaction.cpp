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
