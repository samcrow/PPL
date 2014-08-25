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

#include "advancedoverlaygauge.h"

namespace PPLNAMESPACE {

AdvancedOverlayGauge::AdvancedOverlayGauge(int left2d, int top2d, int width2d, int height2d, int left3d, int top3d, int width3d, int height3d,
                                           int frameOffX, int frameOffY, int textureId3d, bool allow_keyboard, bool is_visible3d,
                                           bool is_visible2d, bool always_draw_3d, bool allow_3d_click, float scale_3d, bool double_size) :
    OverlayGauge(left2d, top2d, width2d, height2d, left3d, top3d, width3d, height3d, frameOffX, frameOffY, textureId3d, allow_keyboard, is_visible3d, is_visible2d, always_draw_3d, allow_3d_click, scale_3d, double_size)
{
}

void AdvancedOverlayGauge::addClickRegion(ClickRegion* region) {
    regions.push_back(region);
}

void AdvancedOverlayGauge::handleNonDragClick(int x_rel, int y_rel) {
    
    // Iterate backwards over the click regions, from last to first added
    for(auto it = regions.rbegin(); it != regions.rend(); it++) {
        // Stop if a region has been clicked on
        bool clicked = (**it).checkForClick(x_rel, y_rel);
        if(clicked) {
            break;
        }
    }
    
}

const std::vector<ClickRegion*>& AdvancedOverlayGauge::clickRegions() {
    return regions;
}

}

