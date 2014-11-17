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

#ifndef LATLON_H
#define LATLON_H
#include "../namespaces.h"
#include <boost/math/constants/constants.hpp>

namespace PPLNAMESPACE {

class LocalPosition;

/**
 * @brief The LatLon class stores a latitude and longitude and provides related operations.
 * 
 */
class LatLon
{
public:
    LatLon();
    LatLon(double latitude, double longitude);
    LatLon(const LocalPosition& local);
    
    double latitude() const;
    double longitude() const;
    
    void setLatitude(double newLatitude);
    void setLongitude(double newLongitude);
    
    /**
     * @brief Returns the distance, in meters, to another point
     * @param other
     * @return 
     */
    double distanceTo(const LatLon& other) const;
    
    /**
     * @brief Returns the bearing, in degrees, to another point
     * @param other
     * @return 
     */
    double bearingTo(const LatLon& other) const;
    
    // Static methods
    
    /**
     * @brief Returns the distance in meters between the two provided points
     * @param p1
     * @param p2
     * @return 
     */
    static double distance(const LatLon& p1, const LatLon& p2);
    
    /**
     * @brief Returns the bearing of the beginning of a great circle path
     * from the `from` point to the `to` point
     * @param from
     * @param to
     * @return 
     */
    static double initialBearing(const LatLon& from, const LatLon& to);
    
    /**
     * @brief Returns the bearing of the end of a great circle path
     * from the `from` point to the `to` point
     * @param from
     * @param to
     * @return 
     */
    static double finalBearing(const LatLon& from, const LatLon& to);
    
private:
    double latitude_ = 0;
    double longitude_ = 0;
    
    /// Mean radius of Earth, in meters
    static constexpr double EARTH_MEAN_RADIUS = 6371000;
    
    static inline double toRadians(double degrees) {
        return degrees / 180 * boost::math::double_constants::pi;
    }
    
    static inline double toDegrees(double radians) {
        return radians * 180 / boost::math::double_constants::pi;
    }
    
};

}
#endif // LATLON_H
