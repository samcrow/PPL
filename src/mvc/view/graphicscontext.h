#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H
#include "../../namespaces.h"
#include <string>

namespace PPLNAMESPACE {

/**
 * @brief The Color struct stores a color.
 * All values are ratios in the range 0 to 1.
 */
struct Color {
    
    Color(float red, float green, float blue, float alpha) :
        red(red),
        green(green),
        blue(blue),
        alpha(alpha)
    {}
    //! @brief Initializes a solid black color
    Color() :
        red(0),
        green(0),
        blue(0),
        alpha(1)
    {}
    
    float red;
    float green;
    float blue;
    
    float alpha;
};

/**
 * @brief The GraphicsContext class provides an interface
 * that code can use to draw simple graphics in a way that does
 * not depend on OpenGL or other low-level interfaces.
 * 
 * A GraphicsContext defines an area in which graphics should be drawn.
 * It is bounded by the top(), bottom(), left(), and right() dimensions.
 * 
 */
class GraphicsContext {
public:
    // Fill and stroke section:
    /**
     * @brief Sets the stroke color
     */
    virtual void setStroke(const Color& newStrokeColor) = 0;
    /**
     * @brief Sets the stroke width, in pixels
     */
    virtual void setStrokeWidth(float width) = 0;
    /**
     * @brief Sets the fill color
     */
    virtual void setFill(const Color& newFillColor) = 0;
    
    // Draw area section:
    virtual float top() = 0;
    virtual float bottom() = 0;
    virtual float left() = 0;
    virtual float right() = 0;
    
    // Rectangle section:
    
    virtual void fillRect(float top, float left, float bottom, float right) = 0;
    
    virtual void strokeRect(float top, float left, float bottom, float right, float width = 1) = 0;
    
    // Text section
    
    /**
     * @brief The fonts supported by the GraphicsContext
     */
    enum Typeface {
        Proportional,
        Monospace,
    };
    enum Alignment {
        Left = 0,
        Center,
        Right,
    };
    
    /**
     * @brief Draws text
     * @param text The string to draw
     * @param x The X location of the lower left corner of the text
     * @param y The Y location of the lower left corner of the text
     * @param face The typeface to draw
     * @param size The font size in points to draw
     */
    virtual void strokeText(std::string text, float x, float y, Typeface face = Proportional, unsigned int size = 12) = 0;
    
    /**
     * @brief Draws text, center aligned and centerd horizontally
     * and vertically on the given center point
     * @param text
     * @param centerX
     * @param centerY
     * @param face
     * @param size
     */
    virtual void strokeTextCentered(std::string text, float centerX, float centerY, Typeface face = Proportional, unsigned int size = 12) = 0;
};

}
#endif // GRAPHICSCONTEXT_H
