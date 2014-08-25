#ifndef ADVANCEDOVERLAYGAUGE_H
#define ADVANCEDOVERLAYGAUGE_H
#include "../../namespaces.h"
#include "../../overlaygauge.h"
#include <vector>
#include "clickregion/clickregion.h"

namespace PPLNAMESPACE {

/**
 * @brief An overlay gauge with support for click regions
 */
class AdvancedOverlayGauge : public OverlayGauge
{
public:
    AdvancedOverlayGauge(int left2d, int top2d, int width2d, int height2d, int left3d, int top3d, int width3d, int height3d,
                         int frameOffX, int frameOffY, int textureId3d, bool allow_keyboard = true, bool is_visible3d = true, bool is_visible2d = false, bool always_draw_3d = false, bool allow_3d_click = true, float scale_3d = 1.0f, bool double_size = false);
    
    void handleNonDragClick(int x_rel, int y_rel);
    
    void addClickRegion(ClickRegion* region);
    
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
    
};

}
#endif // ADVANCEDOVERLAYGAUGE_H
