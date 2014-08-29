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

#ifndef ADVANCEDOVERLAYGAUGE_H
#define ADVANCEDOVERLAYGAUGE_H
#include "../../namespaces.h"
#include "../../overlaygauge.h"
#include <vector>
#include "clickregion/clickregion.h"

namespace PPLNAMESPACE {

/**
 * @brief An overlay gauge with support for click regions
 * 
 * 
 */
class AdvancedOverlayGauge : public OverlayGauge
{
public:
    AdvancedOverlayGauge(int left2d, int top2d, int width2d, int height2d, int left3d, int top3d, int width3d, int height3d,
                         int frameOffX, int frameOffY, int textureId3d, bool allow_keyboard = true, bool is_visible3d = true, bool is_visible2d = false, bool always_draw_3d = false, bool allow_3d_click = true, float scale_3d = 1.0f, bool double_size = false);
    
    void handleNonDragClick(int x_rel, int y_rel);
    
    void addClickRegion(ClickRegion* region);
    
    // Reimplementations to set the cursor based on 
    virtual XPLMCursorStatus handle2dCursorCallback(XPLMWindowID window_id, int x, int y);
    virtual XPLMCursorStatus handle3dCursorCallback(XPLMWindowID window_id, int x, int y);
    
    /**
     * @brief Re-implements draw. Subclasses should override advancedDraw()
     * instead of this method.
     * @param left
     * @param top
     * @param right
     * @param bottom
     */
    virtual void draw(int left, int top, int right, int bottom) final override;
    
    /**
     * @brief Called like draw() to paint graphics
     * @param left
     * @param top
     * @param right
     * @param bottom
     */
    virtual void advancedDraw(int left, int top, int right, int bottom) = 0;
    
    /**
     * @return A const reference to the list of regions
     * that this gauge contains
     */
    const std::vector<ClickRegion*>& clickRegions();
    
private:
    
    /**
     * @brief Contains all the regions registered, from first to last
     */
    std::vector<ClickRegion*> regions;
    
    CursorType customCursor = CursorType::Default;
    
    int mouseX = 0;
    int mouseY = 0;

    void drawCursor(int left, int top, int right, int bottom);
};

}
#endif // ADVANCEDOVERLAYGAUGE_H
