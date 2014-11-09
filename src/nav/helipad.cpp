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

#include "helipad.h"

namespace PPLNAMESPACE {

// Set up defaults
Helipad::Helipad() :
    heading_(0),
    length_(1),
    width_(1),
    surface_(Surface::Asphalt),
    shoulder_(Shoulder::None),
    roughness_(0),
    hasEdgeLights_(false)
{
}

std::string Helipad::name() const {
    return name_;
}
void Helipad::setName(const std::string& newName) {
    name_ = newName;
}

double Helipad::heading() const {
    return heading_;
}
void Helipad::setHeading(double newHeading) {
    heading_ = newHeading;
}
double Helipad::length() const {
    return length_;
}
void Helipad::setLength(double newLength) {
    length_ = newLength;
}
double Helipad::width() const {
    return width_;
}
void Helipad::setWidth(double newWidth) {
    width_ = newWidth;
}
Helipad::Surface Helipad::surface() const {
    return surface_;
}
void Helipad::setSurface(Surface newSurface) {
    surface_ = newSurface;
}
Helipad::Shoulder Helipad::shoulder() const {
    return shoulder_;
}
void Helipad::setShoulder(Shoulder newShoulder) {
    shoulder_ = newShoulder;
}
float Helipad::roughness() const {
    return roughness_;
}
void Helipad::setRoughness(float newRoughness) {
    roughness_ = newRoughness;
}
bool Helipad::hasEdgeLights() const {
    return hasEdgeLights_;
}
void Helipad::setEdgeLights(bool newHasEdgeLights) {
    hasEdgeLights_ = newHasEdgeLights;
}

}
