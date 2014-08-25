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
