#include "glgraphicscontext.h"

#if APL == 1
#include <GL/glew.h>
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

namespace PPLNAMESPACE {

GLGraphicsContext::GLGraphicsContext(float top, float bottom, float left, float right) :
    BasicGraphicsContext(top, bottom, left, right),
    fontCache(fontManager)
{
}


void GLGraphicsContext::fillRect(float top, float left, float bottom, float right)
{
    setGlColor(fillColor());
    glBegin(GL_POLYGON);
    glVertex2f(left, bottom);
    glVertex2f(left, top);
    glVertex2f(right, top);
    glVertex2f(right, bottom);
    glEnd();
}

void GLGraphicsContext::strokeRect(float top, float left, float bottom, float right, float width)
{
    setGlColor(strokeColor());
    glPushAttrib (GL_LINE_BIT);
    glLineWidth(width);
    glBegin(GL_LINE_LOOP);
    glVertex2f(left, bottom);
    glVertex2f(left, top);
    glVertex2f(right, top);
    glVertex2f(right, bottom);
    glEnd();
    
    // Corner note: OpenGL draws lines with ugly corners (it does not
    // miter or bevel them). Some future implementation could
    // add mitering.
    
    
    glPopAttrib();
}

void GLGraphicsContext::strokeText(std::string text, float x, float y, Typeface face, unsigned int size)
{
    FontHandle font = fontCache.get(face, size);
    Color color = strokeColor();
    
    fontManager.drawString(font, reinterpret_cast<float*>(&color), x, y, ALIGN_LEFT, text.c_str());
    
}

void GLGraphicsContext::strokeTextCentered(std::string text, float centerX, float centerY, Typeface face, unsigned int size) {
    FontHandle font = fontCache.get(face, size);
    Color color = strokeColor();
    
    // From the center position, get the bounding box
    const float halfWidth = fontManager.measureString(font, size, text.c_str()) / 2.0;
    
    const float left = centerX - halfWidth;
    const float right = centerX + halfWidth;
    const float bottom = centerY - fontManager.getLineDescent(font, size);
    const float top = centerY + fontManager.getLineAscent(font, size);
    
    const char* start = text.c_str();
    const char* end = start + text.length();
    
    
    fontManager.drawRange(font, reinterpret_cast<float*>(&color), left, bottom, right, top, start, end, ALIGN_CENTER);
    
}

void GLGraphicsContext::setGlColor(const Color &color) {
    glColor4f(color.red, color.green, color.blue, color.alpha);
}

GLGraphicsContext::~GLGraphicsContext() {
    
}

}
