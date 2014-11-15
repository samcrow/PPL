#include "navaidfinder.h"
#include <XPLMNavigation.h>

namespace PPLNAMESPACE {

NavaidFinder& NavaidFinder::type(Navaid::Type type) {

    criteria.emplace_back(
    [type] (XPLMNavRef ref) {
        XPLMNavType xplmType;
        XPLMGetNavAidInfo(ref, &xplmType, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        const Navaid::Type thisType = static_cast<Navaid::Type>(xplmType);
        return static_cast< bool >(thisType & type);
    });

    return *this;
}

NavaidFinder& NavaidFinder::proximity(LatLon position, double maxDistance) {
    criteria.emplace_back(
    [position, maxDistance] (XPLMNavRef ref) {
        float latitude;
        float longitude;
        XPLMGetNavAidInfo(ref, nullptr, &latitude, &longitude, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        return position.distanceTo({ latitude, longitude }) <= maxDistance;
    });

    return *this;
}

NavaidFinder::list_type NavaidFinder::search() {
    list_type navaids;

    for(auto iter = NavRefIterator::begin(); iter != NavRefIterator::end(); iter++ )
    {
        // Ensure that each criterion returns true for this ref
        bool matched = true;
        for(const criterion& cr : criteria) {
            if(!cr(*iter)) {
                matched = false;
                break;
            }
        }
        if(matched) {
            navaids.emplace_back(Navaid::build(*iter));
        }
    }

    return navaids;
}

NavaidFinder::list_type NavaidFinder::findAllNavaids() {

    list_type navaids;

    for(auto iter = NavRefIterator::begin(); iter != NavRefIterator::end(); iter++ )
    {
        navaids.emplace_back(Navaid::build(*iter));
    }

    return navaids;
}

NavaidFinder::list_type NavaidFinder::findNavaidsWithType(Navaid::Type type) {
    list_type navaids;

    for(auto iter = NavRefIterator::begin(); iter != NavRefIterator::end(); iter++ )
    {
        XPLMNavType xplmType;
        XPLMGetNavAidInfo(*iter, &xplmType, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        const Navaid::Type thisType = static_cast<Navaid::Type>(xplmType);
        // Check for any bit in common
        if( static_cast<bool>( type & thisType )) {
            navaids.emplace_back(Navaid::build(*iter));
        }
    }

    return navaids;
}

}
