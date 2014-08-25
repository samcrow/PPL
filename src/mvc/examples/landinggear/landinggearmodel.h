#ifndef LANDINGGEARMODEL_H
#define LANDINGGEARMODEL_H
#include "../../../namespaces.h"


namespace PPLNAMESPACE {

/**
 * @brief The LandingGearModel class defines the data
 * used for landing gear control
 */
class LandingGearModel
{
public:
    LandingGearModel() {}
    
    /**
     * @return The current ratio of landing gear deployment. 0
     * is fully retracted, 1 is fully deployed.
     */
    virtual float deployRatio() = 0;
    
    /**
     * @brief Sets whether the landing gear should attempt to extend
     * @param deployRatio
     */
    virtual void setExtended(bool extended) = 0;
    
    virtual ~LandingGearModel() {}
};


}
#endif // LANDINGGEARMODEL_H
