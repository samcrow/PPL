#ifndef OVERLAYGAUGEVIEW_H
#define OVERLAYGAUGEVIEW_H
#include "advancedoverlaygauge.h"
#include "../view.h"
#include "glgraphicscontext.h"
#include "clickregion/clickregion.h"

namespace PPLNAMESPACE {

template < class ControllerType >
class OverlayGaugeView : public AdvancedOverlayGauge, public View < ControllerType >
{
public:
    OverlayGaugeView(int width, int height, ControllerType& controller) :
        AdvancedOverlayGauge(300, 300, width, height, 300, 300, width, height, 0, 0, 0, true, true, true),
        View<ControllerType>(controller),
        
        context(height, 0, 0, width)
    {}
    
    void draw(int, int, int, int)
    {
        View<ControllerType>::controller().draw(context);
        drawClickRegions();
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
