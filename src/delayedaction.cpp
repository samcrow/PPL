#include "delayedaction.h"

namespace PPLNAMESPACE {


void DelayedAction::schedule(float timeSeconds, delayed_function fn) {
    
    // Allocate the action on the heap. It will delete itself when it is done.
    new DelayedAction(timeSeconds, fn);
}

DelayedAction::DelayedAction(float timeSeconds, delayed_function fn) :
    fn(fn)

{
    // Create a flight loop and register it to be called after the required time
    XPLMCreateFlightLoop_t params;
    params.structSize = sizeof(XPLMCreateFlightLoop_t);
    params.phase = xplm_FlightLoop_Phase_BeforeFlightModel;
    params.callbackFunc = &DelayedAction::callback;
    params.refcon = this;
    
    loopId = XPLMCreateFlightLoop(&params);
    // Schedule the loop to be called
    XPLMScheduleFlightLoop(loopId, timeSeconds, true);
}

float DelayedAction::callback(float, float, int, void* inRefCon) {
    DelayedAction* action = static_cast<DelayedAction*>(inRefCon);
    // Call the function
    action->fn();
    
    // Delete the flight loop
    XPLMDestroyFlightLoop(action->loopId);
    
    // Delete the action from the heap
    delete action;
    
    // Don't get called again
    return 0;
}

}
