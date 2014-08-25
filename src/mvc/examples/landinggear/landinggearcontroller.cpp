#include "landinggearcontroller.h"
#include "landinggearmodelxplane.h"
#include <cmath>
#include <iostream>

namespace PPLNAMESPACE {


LandingGearController::LandingGearController(LandingGearModel &model) :
    Controller("Landing gear", model),
    PPL::Processor(),
    lastDeployRatio(NAN)
{
}

void LandingGearController::retract() {
    model().setExtended(false);
}

void LandingGearController::deploy() {
    model().setExtended(true);
}

boost::signals2::connection LandingGearController::addExtendFinishedListener(const listener_type& listener) {
    return extendedSignal.connect(listener);
}
boost::signals2::connection LandingGearController::addRetractFinishedListener(const listener_type& listener) {
    return retractedSignal.connect(listener);
}
boost::signals2::connection LandingGearController::addExtendStartedListener(const listener_type &listener) {
    return extensionStartedSignal.connect(listener);
}
boost::signals2::connection LandingGearController::addRetractStartedListener(const listener_type &listener) {
    return retractionStartedSignal.connect(listener);
}

LandingGearController::~LandingGearController() {
    
}


// Flight loop callback
float LandingGearController::callback(float, float, int)
{
    
    // Get deploy ratio from the model
    float deployRatio = model().deployRatio();
    
    // See if deploy ratio has changed
    if(std::isnan(lastDeployRatio)) {
        // Deploy ratio not yet set. Don't do any of the following conditions
    }
    else if(isBasicallyOne(deployRatio) && !isBasicallyOne(lastDeployRatio)) {
        // Just finished deploying
        extendedSignal();
    }
    else if(isBasicallyZero(deployRatio) && !isBasicallyZero(lastDeployRatio)) {
        // Just finished retracting
        retractedSignal();
    }
    else if(!isBasicallyZero(deployRatio) && isBasicallyZero(lastDeployRatio)) {
        // Just started extending
        extensionStartedSignal();
    }
    else if(!isBasicallyOne(deployRatio) && isBasicallyOne(lastDeployRatio)) {
        // Just started retracting
        retractionStartedSignal();
    }
    
    lastDeployRatio = deployRatio;
    
    return -1;
}

bool LandingGearController::isBasicallyOne(float value) {
    return value > 0.999999f;
}

bool LandingGearController::isBasicallyZero(float value) {
    return value < 0.0000001f;
}

}
