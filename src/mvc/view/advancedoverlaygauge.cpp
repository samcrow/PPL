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
    
    // Iterate backwards over the click regions, from most last to first added
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

