#include "landinggearmodelxplane.h"


namespace PPLNAMESPACE {



LandingGearModelXPlane::LandingGearModelXPlane() :
    LandingGearModel(),
    deployRatioDataref("sim/flightmodel2/gear/deploy_ratio"),
    gearHandleDataref("sim/cockpit2/controls/gear_handle_down", PPL::ReadWrite)
{
}


float LandingGearModelXPlane::deployRatio()
{
    // Average deploy ratios 0-2
    float sum = deployRatioDataref[0] + deployRatioDataref[1] + deployRatioDataref[2];
    return sum / 3;
}

void LandingGearModelXPlane::setExtended(bool extended)
{
    gearHandleDataref = extended;
}

LandingGearModelXPlane::~LandingGearModelXPlane() {
    
}

}
