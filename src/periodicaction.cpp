#include "periodicaction.h"
#include <stdexcept>

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
