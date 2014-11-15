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

#ifndef OVERLAYGAUGEVIEW_H
#define OVERLAYGAUGEVIEW_H
#include "advancedoverlaygauge.h"
#include "../view.h"
#include "glgraphicscontext.h"
#include "clickregion/clickregion.h"

namespace PPLNAMESPACE {

/**
 * A View that displays an OverlayGauge
 */
template < class ControllerType >
class OverlayGaugeView : public AdvancedOverlayGauge, public View < ControllerType >
{
public:
    OverlayGaugeView(FontCache& fontCache, int width, int height, ControllerType& controller) :
        AdvancedOverlayGauge(300, 300, width, height, 300, 300, width, height, 0, 0, 0, true, true, true),
        View<ControllerType>(controller),
        
        context(fontCache, height, 0, 0, width)
    {}
    
    virtual void advancedDraw(int, int, int, int) override
    {
        View<ControllerType>::controller().draw(context);
    }
    
    void handleKeyPress(char, XPLMKeyFlags, char) {
        
    }
    
private:
    GLGraphicsContext context;
    
    /**
     * @brief Draws outlines of this view's click regions
     */
    void drawClickRegions() {
        context.setStroke(Color(0.83, 0.78, 0.57, 1));
        for(ClickRegion* region : clickRegions()) {
            context.strokeRect(region->top(), region->left(), region->bottom(), region->right());
        }
    }
};

}
#endif // OVERLAYGAUGEVIEW_H
