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

#ifndef LOCALPOSITION_H
#define LOCALPOSITION_H
#include "../namespaces.h"

namespace PPLNAMESPACE {

class LatLon;

/**
 * Stores a position in local coordinates. All values are in meters.
 *
 * Coordinate system information is available at http://www.xsquawkbox.net/xpsdk/mediawiki/Category:XPLMGraphics .
 */
class LocalPosition
{
public:
    /// Default constructor. Sets X, Y, and Z to zero
    LocalPosition();

    LocalPosition(double x, double y, double z);

    /**
     * Constructs a local position at the provided altitude
     * from a latitude/longitude point
     * @param latLon
     * @param altitude
     */
    LocalPosition(const LatLon& latLon, double altitude = 0);

    /**
     * Constructs a local position at mean sea level
     * from a latitude/longitude point
     * @param latLon
     */
    LocalPosition(const LatLon& latLon);

    double x() const;
    double y() const;
    double z() const;

    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);

    /**
     *
     * @param other
     * @return The distance, in meters, from this point to the other point
     */
    double distanceTo(const LocalPosition& other) const;

    // Static methods

    /**
     *
     * @param p1
     * @param p2
     * @return The distance, in meters, between the two provided points
     */
    static double distance(const LocalPosition& p1, const LocalPosition& p2);

private:
    double x_;
    double y_;
    double z_;
};

}
#endif // LOCALPOSITION_H
