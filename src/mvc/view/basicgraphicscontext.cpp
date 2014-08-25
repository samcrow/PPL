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

#include "basicgraphicscontext.h"

namespace PPLNAMESPACE {

BasicGraphicsContext::BasicGraphicsContext(float top, float bottom, float left, float right) :
    top_(top),
    bottom_(bottom),
    left_(left),
    right_(right)
{
}

const Color& BasicGraphicsContext::fillColor() {
    return fillColor_;
}

const Color& BasicGraphicsContext::strokeColor() {
    return strokeColor_;
}

float BasicGraphicsContext::strokeWidth() {
    return strokeWidth_;
}

void BasicGraphicsContext::setStroke(const Color& newStrokeColor)
{
    strokeColor_ = newStrokeColor;
}

void BasicGraphicsContext::setStrokeWidth(float width)
{
    strokeWidth_ = width;
}

void BasicGraphicsContext::setFill(const Color& newFillColor)
{
    fillColor_ = newFillColor;
}

float BasicGraphicsContext::top() {
    return top_;
}
float BasicGraphicsContext::bottom() {
    return bottom_;
}
float BasicGraphicsContext::left() {
    return left_;
}
float BasicGraphicsContext::right() {
    return right_;
}

}
