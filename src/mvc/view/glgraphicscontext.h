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

#ifndef GLGRAPHICSCONTEXT_H
#define GLGRAPHICSCONTEXT_H

#include "../../namespaces.h"
#include "basicgraphicscontext.h"
#include "../../fontmgr.h"
#include "fontcache.h"
#include <cassert>

class GLUtesselator;

namespace PPLNAMESPACE {

/**
 * @brief The GLGraphicsContext class is a GraphicsContext implementation
 * that uses OpenGL for drawing.
 */
class GLGraphicsContext : public BasicGraphicsContext
{
public:
    GLGraphicsContext(float top, float bottom, float left, float right);
    
    
    void fillRect(float top, float left, float bottom, float right);
    void strokeRect(float top, float left, float bottom, float right, float width = 1);
    
    virtual void fillPolygon(double* points, int pointCount);


    virtual void strokeText(const std::string& text, float x, float y, Typeface face, unsigned int size, bool drawBox = false) override;
    
    virtual void strokeTextCentered(const std::string& text, float centerX, float centerY, Typeface face = Proportional, unsigned int size = 12, bool drawBox = false) override;
    
    virtual ~GLGraphicsContext();
private:
    
    static void setGlColor(const Color& color);
    
    FontMgr fontManager;
    FontCache fontCache;

    GLUtesselator* tesselator;


    /// Typedef for a GLUT callback: No parameters, returns void
    /// The acual callbacks have different function signatures
    typedef void (*glu_callback) (void);

    /// Converts the provided function object into
    /// a GLUT callback
    /// F is the type of function object provided. This cannot be an std::function.
    /// It is usually a lambda type, obtained indirectly using decltype().
    /// As are the arguments that the function takes
    template < typename F, typename... As >
    glu_callback makeGluCallback(F function) {
        // Convert the function to a function pointer of the same signature
        typedef void (function_type) (As...);
        typedef function_type* function_pointer;
        function_pointer pointer = static_cast< function_pointer > (function);
        assert(pointer);
        // Unsafe cast into the specified callback type
        return reinterpret_cast< glu_callback >(pointer);
    }
};


}
#endif // GLGRAPHICSCONTEXT_H
