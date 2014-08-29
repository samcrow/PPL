#ifndef CURSOR_H
#define CURSOR_H

#if APL == 1
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#elif IBM == 1
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "GL/glew.h"
#include <gl/gl.h>
#include <gl/glu.h>
#elif LIN == 1
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <XPLMGraphics.h>
#include "../namespaces.h"

namespace PPLNAMESPACE {
class Texture;

class Cursor
{
public:
    
    /**
     * @brief Draws the cursor at the provided coordinates
     * @param x
     * @param y
     */
    void draw(float x, float y) const;
    
protected:
    
    friend class CursorManager;
    
    Cursor(int textureId, GLfloat width, GLfloat height, const GLfloat* textureCoordinates, GLfloat xOffset = 0, GLfloat yOffset = 0);
    
private:
    
    /// The ID of the interface texture to draw
    int textureId;
    
    /// The width of the texture region, in pixels
    GLfloat width;
    /// The height of the texture region, in pixels
    GLfloat height;
    
    /// The coordinates in the texture to draw from
    /**
     * X, Y pairs in clockwise order starting at top left
     * { left, top,
     * right, top,
     * right, bottom,
     * left, bottom }
     */
    GLfloat textureCoordinates[8];
    
    /// The distance to move the cursor right so that it is centered
    /// in the correct place
    GLfloat xOffset;
    
    /// The distance to move the cursor up so that it is centered
    /// in the correct place
    GLfloat yOffset;
};

}
#endif // CURSOR_H
