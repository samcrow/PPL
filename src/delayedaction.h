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
    void setFunction(delayed_function newFunction);
    
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
