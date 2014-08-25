#ifndef DELAYEDACTION_H
#define DELAYEDACTION_H
#include "namespaces.h"
#include <functional>
#include <XPLMProcessing.h>

namespace PPLNAMESPACE {

/**
 * @brief The DelayedAction class allows an operation
 * to be scheduled to be run sometime in the future.
 * 
 * An instance of this class must be set up with a function to call.
 * After schedule(float) is called, the specified time will pass and
 * the function will be called.
 * 
 */
class DelayedAction
{
public:
    typedef std::function< void () > delayed_function;
    
    /**
     * @brief Creates a DelayedAction object that will
     * call the provided function
     * @param fn The function to be called
     */
    DelayedAction(delayed_function fn);
    
    /**
     * @brief Creates a DelayedAction object with an unspecified function
     */
    DelayedAction();
    
    /**
     * @brief Sets the function to be called when the time has expired
     * @param fn
     */
    void setFunction(delayed_function fn);
    
    /**
     * @brief Schedules the function associated with this instance
     * to be called after the specified number of seconds.
     * @param timeSeconds
     * 
     * @throws std::logic_error if a function to be called has not already been set
     */
    void schedule(float timeSeconds);
    
    /**
     * @brief Cancels the execution of this action. If this action
     * has not yet been scheduled, this method has no effect.
     * If this action has been scheduled but has not yet timed out,
     * the function will never be called. If the function has already been called,
     * this method has no effect.
     */
    void cancel();
    
    /**
     * @brief Schedules a function to be called in the future.
     * 
     * After the elapsed time, the provided function will be called.
     * A DelayedAction object will be created and will be deleted automatically.
     * 
     * @param timeSeconds
     * @param fn
     */
    static void schedule(float timeSeconds, delayed_function fn);
    
private:
    
    /**
     * @brief The function to be called when the time has passed
     */
    delayed_function fn;
    
    XPLMFlightLoopID loopId = 0;
    
    /**
     * @brief Called from the X-Plane system when the time has elapsed
     * @param inRefCon
     * @return 
     */
    static float callback(float, float, int, void* inRefCon);
};

}

#endif // DELAYEDACTION_H
