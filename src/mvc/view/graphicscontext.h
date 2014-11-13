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

#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H
#include "../../namespaces.h"
#include <string>
#include <vector>

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

    /**
     * Fills a polygon defined by the given points.
     *
     * The polygon does not need to be convex, but it must not be self-intersecting.
     *
     * @param points The points that define the polygon.
     * This should be an array of length 3 * pointCount.
     * Each group of 3 values represents a point. The three values
     * are in X, Y, Z order.
     *
     * @param pointCount The number of points to draw
     */
    virtual void fillPolygon(double* points, int pointCount) = 0;
    inline void fillPolygon(std::vector<double> points) {
        fillPolygon(&points.front(), points.size());
    }
    
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
     * @param drawBox If a rectangle should be drawn around the text
     */
    virtual void strokeText(const std::string& text, float x, float y, Typeface face = Proportional, unsigned int size = 12, bool drawBox = false) = 0;
    
    /**
     * @brief Draws text, center aligned and centerd horizontally
     * and vertically on the given center point
     * @param text The string to draw
     * @param centerX The X location of the center of the text
     * @param centerY The Y location of the center of the text
     * @param face The typeface to draw
     * @param size The font size in points to draw
     * @param drawBox If a rectangle should be drawn around the text
     */
    virtual void strokeTextCentered(const std::string& text, float centerX, float centerY, Typeface face = Proportional, unsigned int size = 12, bool drawBox = false) = 0;
};

}
#endif // GRAPHICSCONTEXT_H
