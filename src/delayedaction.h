#ifndef DELAYEDACTION_H
#define DELAYEDACTION_H
#include "namespaces.h"
#include <functional>
#include <XPLMProcessing.h>

namespace PPLNAMESPACE {

/**
 * @brief The DelayedAction class allows an operation
 * to be scheduled to be run sometime in the future
 */
class DelayedAction
{
public:
    typedef std::function<void ()> delayed_function;
    
    /**
     * @brief Schedules 
     * @param timeSeconds
     * @param fn
     */
    static void schedule(float timeSeconds, delayed_function fn);
    
private:
    DelayedAction(float timeSeconds, delayed_function fn);
    
    /**
     * @brief The function to be called when the time has passed
     */
    delayed_function fn;
    
    XPLMFlightLoopID loopId;
    
    /**
     * @brief Called from the X-Plane system when the time has elapsed
     * @param inRefCon
     * @return 
     */
    static float callback(float, float, int, void* inRefCon);
};

}

#endif // DELAYEDACTION_H
