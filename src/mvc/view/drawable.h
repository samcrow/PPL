#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "../../namespaces.h"

namespace PPLNAMESPACE {

class GraphicsContext;

/**
 * @brief An interface for a class that can draw things into a GraphicsContext
 */
class Drawable {
public:
    
    /**
     * @brief Draws graphics
     * @param gc The context to use for drawing
     */
    virtual void draw(GraphicsContext& gc) = 0;
    
};

}

#endif // DRAWABLE_H
