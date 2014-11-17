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

#include "latlon.h"
#include "localposition.h"
#include <cmath>
#include <XPLMGraphics.h>

namespace PPLNAMESPACE {

LatLon::LatLon()
{
}

LatLon::LatLon(double latitude, double longitude) :
    latitude_(latitude),
    longitude_(longitude)
{
}

LatLon::LatLon(const LocalPosition& local) {
    double altitude;
    XPLMLocalToWorld(local.x(), local.y(), local.z(), &latitude_, &longitude_, &altitude);
}

double LatLon::latitude() const {
    return latitude_;
}

double LatLon::longitude() const {
    return longitude_;
}

void LatLon::setLatitude(double newLatitude) {
    latitude_ = newLatitude;
}

void LatLon::setLongitude(double newLongitude) {
    longitude_ = newLongitude;
}

/**
 *
 * @param other
 * @return The distance, in meters, between this point and another
 */
double LatLon::distanceTo(const LatLon& other) const {
    return distance(*this, other);
}

double LatLon::bearingTo(const LatLon& other) const {
    return initialBearing(*this, other);
}


// I would like to thank the author of the web page http://www.movable-type.co.uk/scripts/latlong.html
// for describing these techniques:

/**
 *
 * @param p1
 * @param p2
 * @return The distance, in meters, between the two points
 */
double LatLon::distance(const LatLon& p1, const LatLon& p2) {
    // Spherical law of cosines
    // The Haversine version might be better for small distances
    
    const double v1 = toRadians(p1.latitude());
    const double v2 = toRadians(p2.latitude());
    const double dl = toRadians(p2.longitude() - p1.longitude());
    return std::acos( std::sin(v1) * std::sin(v2) + std::cos(v1) * std::cos(v2) * std::cos(dl) ) * EARTH_MEAN_RADIUS;
}

double LatLon::initialBearing(const LatLon& from, const LatLon& to) {
    const double v1 = toRadians(from.latitude());
    const double v2 = toRadians(to.latitude());
    const double l1 = toRadians(from.longitude());
    const double l2 = toRadians(to.longitude());
    
    const double x = std::sin(l2 - l1) * std::cos(v2);
    const double y = std::cos(v1) * std::sin(v2) - std::sin(v1) * std::cos(v2) * std::cos(l2 - l1);
    const double bearingRadians = std::atan2(y, x);
    // Convert to degrees and normalize
    const double degrees = toDegrees(bearingRadians);
    return std::fmod(degrees + 360, 360);
}

double LatLon::finalBearing(const LatLon &from, const LatLon &to) {
    const double initial = initialBearing(from, to);
    return std::fmod(initial + 180, 360);
}

}
