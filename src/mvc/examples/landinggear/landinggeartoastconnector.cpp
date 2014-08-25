#include "landinggeartoastconnector.h"

namespace PPLNAMESPACE {

LandingGearToastConnector::LandingGearToastConnector() :
    display(0)
{
}

void LandingGearToastConnector::onRetracted() {
    if(display != 0) {
        delete display;
    }
    display = new OnScreenDisplay(400, 100, "Landing gear retracted");
    
}

void LandingGearToastConnector::onExtended() {
    if(display != 0) {
        delete display;
    }
    display = new OnScreenDisplay(400, 100, "Landing gear extended");
}


LandingGearToastConnector::~LandingGearToastConnector() {
    if(display != 0) {
        delete display;
    }
}

}
