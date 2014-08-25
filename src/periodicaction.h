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

#ifndef PERIODICACTION_H
#define PERIODICACTION_H
#include <functional>
#include <XPLMProcessing.h>

/**
 * @brief The PeriodicAction class manages a function
 * that can be called periodically.
 * 
 * The period of an action can be changed by cancelling it
 * and then rescheduling it with a different period.
 */
class PeriodicAction
{
public:
    
    typedef std::function< void () > periodic_function;
    
    /**
     * @brief Constructs a PeriodicAction with no function
     */
    PeriodicAction();
    
    /**
     * @brief Constructs a PeriodicAction that will call the provided function
     * @param fn
     */
    PeriodicAction(periodic_function fn);
    
    /**
     * @brief Sets the function to be periodically called
     * @param newFunction
     */
    void setFunction(periodic_function newFunction);
    
    /**
     * @brief Schedules the function to be called with the given period.
     * A function must have already been set.
     * 
     * Because the period provided here is the time from the end of a callback
     * until the beginning of the next, and because timing is not perfectly precise,
     * the actual period will be slightly larger than this value.
     * 
     * @param periodSeconds The number of seconds that should pass in between calls
     * 
     * @throws std::logic_error if a function to be called has not already been set
     */
    void schedule(float periodSeconds);
    
    /**
     * @brief Stops the execution of this periodic action.
     * 
     * If this action has not yet been scheduled or has been cancelled, this method
     * has no effect.
     * 
     * An action can safely be cancelled and then scheduled again any number of times.
     */
    void cancel();
    
private:
    
    /**
     * @brief The function to be called
     */
    periodic_function fn;
    
    /**
     * @brief The period, in seconds, between function calls
     */
    float period;
    
    /**
     * @brief The ID of the current flight loop, or 0 if none is active
     */
    XPLMFlightLoopID loopId = 0;
    
    /**
     * @brief Called from the X-Plane system when the time has elapsed
     * @param inRefCon
     * @return 
     */
    static float callback(float, float, int, void* inRefCon);
    
};

#endif // PERIODICACTION_H
