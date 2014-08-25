#ifndef LANDINGGEARTOASTCONNECTOR_H
#define LANDINGGEARTOASTCONNECTOR_H
#include "../../../namespaces.h"
#include "../../../onscreendisplay.h"

namespace PPLNAMESPACE {

class LandingGearToastConnector
{
public:
    LandingGearToastConnector();
    
    void onRetracted();
    void onExtended();
    
    virtual ~LandingGearToastConnector();
    
private:
    
    OnScreenDisplay* display;
};



}
#endif // LANDINGGEARTOASTCONNECTOR_H

