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

#ifndef BASICGRAPHICSCONTEXT_H
#define BASICGRAPHICSCONTEXT_H

#include "graphicscontext.h"

namespace PPLNAMESPACE {

/**
 * @brief A type of graphics context that keeps track
 * of the colors and other parameters that have been set.
 */
class BasicGraphicsContext : public GraphicsContext
{
public:
    BasicGraphicsContext(float top, float bottom, float left, float right);
    
    virtual void setStroke(const Color &newStrokeColor);
    virtual void setStrokeWidth(float width);
    virtual void setFill(const Color &newFillColor);
    
    virtual float top();
    virtual float bottom();
    virtual float left();
    virtual float right();
    
protected:
    
    const Color& fillColor();
    const Color& strokeColor();
    float strokeWidth();
    
private:
    Color fillColor_;
    Color strokeColor_;
    float strokeWidth_;
    
    float top_;
    float bottom_;
    float left_;
    float right_;
    
};

}
#endif // BASICGRAPHICSCONTEXT_H
