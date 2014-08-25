#ifndef GLGRAPHICSCONTEXT_H
#define GLGRAPHICSCONTEXT_H
#include "../../namespaces.h"
#include "basicgraphicscontext.h"
#include "../../fontmgr.h"
#include "fontcache.h"

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
    
   
    virtual void strokeText(std::string text, float x, float y, Typeface face, unsigned int size);
    
    virtual void strokeTextCentered(std::string text, float centerX, float centerY, Typeface face = Proportional, unsigned int size = 12);
    
    virtual ~GLGraphicsContext();
private:
    
    static void setGlColor(const Color& color);
    
    FontMgr fontManager;
    FontCache fontCache;
};


}
#endif // GLGRAPHICSCONTEXT_H
