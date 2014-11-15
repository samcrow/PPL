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

#include "glgraphicscontext.h"
#include <XPLMGraphics.h>
#include "../../namespaces.h"
#include "basicgraphicscontext.h"
#include "../../fontmgr.h"
#include "fontcache.h"

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

namespace PPLNAMESPACE {

GLGraphicsContext::GLGraphicsContext(FontCache& fontCache, float top, float bottom, float left, float right) :
    BasicGraphicsContext(top, bottom, left, right),
    fontCache(fontCache),
    fontManager(this->fontCache.fontManager()),
    tesselator(nullptr)
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

void GLGraphicsContext::fillPolygon(double* points, int pointCount) {
    // Initialize tesselator
    if(!tesselator) {
        tesselator = gluNewTess();
    }
    setGlColor(fillColor());
    // Specify fill
    gluTessProperty(tesselator, GLU_TESS_BOUNDARY_ONLY, GL_FALSE);
    // Set up callbacks
    gluTessCallback(tesselator, GLU_TESS_BEGIN, makeGluCallback< decltype(&glBegin), GLenum >( &glBegin ));
    gluTessCallback(tesselator, GLU_TESS_END, makeGluCallback(&glEnd));
    gluTessCallback(tesselator, GLU_TESS_VERTEX, makeGluCallback<decltype(&glVertex3dv), const double* >(&glVertex3dv));

    gluTessBeginPolygon(tesselator, nullptr);
    gluTessBeginContour(tesselator);

    // Specify vertices
    for(int i = 0; i < pointCount; i++) {
        gluTessVertex(tesselator, points + i * 3, points + i * 3);
    }

    gluTessEndContour(tesselator);
    gluTessEndPolygon(tesselator);
}
void GLGraphicsContext::strokePolygon(double* points, int pointCount, float width) {
    // Initialize tesselator
    if(!tesselator) {
        tesselator = gluNewTess();
    }
    setGlColor(strokeColor());
    glLineWidth(width);
    // Specify line
    gluTessProperty(tesselator, GLU_TESS_BOUNDARY_ONLY, GL_TRUE);

    // Set up callbacks
    gluTessCallback(tesselator, GLU_TESS_BEGIN, makeGluCallback< decltype(&glBegin), GLenum >( &glBegin ));
    gluTessCallback(tesselator, GLU_TESS_END, makeGluCallback(&glEnd));
    gluTessCallback(tesselator, GLU_TESS_VERTEX, makeGluCallback<decltype(&glVertex3dv), const double* >(&glVertex3dv));

    gluTessBeginPolygon(tesselator, nullptr);
    gluTessBeginContour(tesselator);

    // Specify vertices
    for(int i = 0; i < pointCount; i++) {
        gluTessVertex(tesselator, points + i * 3, points + i * 3);
    }

    gluTessEndContour(tesselator);
    gluTessEndPolygon(tesselator);
}

void GLGraphicsContext::strokeText(const std::string& text, float x, float y, Typeface face, unsigned int size, bool drawBox)
{
    FontHandle font = fontCache.get(face, size);
    Color color = strokeColor();
    
    fontManager.drawString(font, reinterpret_cast<float*>(&color), x, y, ALIGN_LEFT, text.c_str());
    
    if(drawBox) {
        
        const float width = fontManager.measureString(font, size, text.c_str());
        const float height = fontManager.getLineAscent(font, size) + fontManager.getLineDescent(font, size);
        // Inconvenient constant offsets to make the box look nice
        strokeRect(y + height + 2, x - 4, y + 1, x + width + 4);
    }
}

void GLGraphicsContext::strokeTextCentered(const std::string& text, float centerX, float centerY, Typeface face, unsigned int size, bool drawBox) {
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
    
    if(drawBox) {
        // Inconvenient constant offsets to make the box look nice
        strokeRect(top + 2, left - 4, bottom + 1, right + 4);
    }
    
}

void GLGraphicsContext::setGlColor(const Color &color) {
    glColor4f(color.red, color.green, color.blue, color.alpha);
}

GLGraphicsContext::~GLGraphicsContext() {
    if(tesselator) {
        gluDeleteTess(tesselator);
    }
}

}
