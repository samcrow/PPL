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

#include "localposition.h"
#include "latlon.h"
#include <XPLMGraphics.h>
#include <cmath>

namespace PPLNAMESPACE {

LocalPosition::LocalPosition() :
    x_(0),
    y_(0),
    z_(0)
{
}

LocalPosition::LocalPosition(double x, double y, double z) :
    x_(x),
    y_(y),
    z_(z)
{
}

LocalPosition::LocalPosition(const LatLon& latLon) :
    LocalPosition(latLon, 0)
{
}

LocalPosition::LocalPosition(const LatLon& latLon, double altitude) {
    XPLMWorldToLocal(latLon.latitude(), latLon.longitude(), altitude, &x_, &y_, &z_);
}

double LocalPosition::x() const {
    return x_;
}
double LocalPosition::y() const {
    return y_;
}
double LocalPosition::z() const {
    return z_;
}
void LocalPosition::setX(double newX) {
    x_ = newX;
}
void LocalPosition::setY(double newY) {
    y_ = newY;
}
void LocalPosition::setZ(double newZ) {
    z_ = newZ;
}

double LocalPosition::distanceTo(const LocalPosition& other) const {
    return distance(*this, other);
}

double LocalPosition::distance(const LocalPosition& p1, const LocalPosition& p2)
{
    const double dx = p1.x() - p2.x();
    const double dy = p1.y() - p2.y();
    const double dz = p1.z() - p2.z();
    return std::sqrt( dx * dx + dy * dy + dz * dz );
}

}
