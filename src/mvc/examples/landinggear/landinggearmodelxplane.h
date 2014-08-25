#ifndef LANDINGGEARMODELXPLANE_H
#define LANDINGGEARMODELXPLANE_H
#include "../../../dataref.h"

#include "landinggearmodel.h"

namespace PPLNAMESPACE {

/**
 * @brief The LandingGearModelXPlane class implements LandingGearModel
 * using X-Plane datarefs
 */
class LandingGearModelXPlane : public LandingGearModel
{
public:
    LandingGearModelXPlane();
    
    
    virtual float deployRatio();
    
    virtual void setExtended(bool extended);
    
    virtual ~LandingGearModelXPlane();
private:
    
    PPL::DataRef<std::vector<float> > deployRatioDataref;
    PPL::DataRef<int> gearHandleDataref;
    
};

}
#endif // LANDINGGEARMODELXPLANE_H
