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

#ifndef LANDINGGEARCONTROLLER_H
#define LANDINGGEARCONTROLLER_H
#include "../../controller.h"
#include "landinggearmodel.h"
#include "../../../processor.h"
#include <boost/signals2.hpp>
#include "../../../namespaces.h"

namespace PPLNAMESPACE {

class LandingGearController : public Controller < LandingGearModel >, private PPL::Processor
{
public:
    LandingGearController(LandingGearModel& model);
    
    virtual ~LandingGearController();
    
    virtual float callback(float, float, int);
    
    /**
     * @brief Starts the landing gear deployment process
     */
    void deploy();
    /**
     * @brief Starts the landing gear retraction process
     */
    void retract();
    
    typedef boost::signals2::signal<void ()> signal_type;
    
    typedef signal_type::slot_type listener_type;
    
    boost::signals2::connection addExtendFinishedListener(const listener_type& listener);
    boost::signals2::connection addRetractFinishedListener(const listener_type& listener);
    boost::signals2::connection addExtendStartedListener(const listener_type& listener);
    boost::signals2::connection addRetractStartedListener(const listener_type& listener);
    
private:
    float lastDeployRatio;
    
    /**
     * @brief A signal emitted when the landing gear has finished extending
     */
    signal_type extendedSignal;
    /**
     * @brief A signal emitted when the landing gear has finished retracting
     */
    signal_type retractedSignal;
    /**
     * @brief A signal emitted when the landing gear has started extending
     */
    signal_type extensionStartedSignal;
    /**
     * @brief A signal emitted when the landing gear has started retracting
     */
    signal_type retractionStartedSignal;
    
    static bool isBasicallyZero(float value);
    static bool isBasicallyOne(float value);
};

}
#endif // LANDINGGEARCONTROLLER_H
