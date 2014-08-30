#include "cursormanager.h"
#include "../pluginpath.h"
#include <XPLMGraphics.h>

namespace PPLNAMESPACE {

std::unique_ptr<CursorManager> CursorManager::instance_ptr;

/// Width of the interface bitmap
static const int INTERFACE_WIDTH = 512;
static const int INTERFACE_HEIGHT = 512;

CursorManager::CursorManager() :
    interfaceTextureId(XPLMGetTexture(xplm_Tex_GeneralInterface))
{
    
}

CursorManager& CursorManager::getInstance() {
    if(!instance_ptr) {
        instance_ptr.reset(new CursorManager());
    }
    return *instance_ptr;
}

Cursor& CursorManager::getCursor(CursorType type) {
    try {
        return cache.at(type);
    }
    catch(std::out_of_range&) {
        // No cursor in cache; need to create
        Cursor cursor = createCursor(type);
        cache.insert(std::make_pair(type, cursor));
        return cache.at(type);
    }
}

Cursor CursorManager::createCursor(CursorType type) {
    
    // Coordinate system: Origin in lower left corner
    
    switch(type) {
    case CursorType::ArrowUp: {
        const int width = 27;
        const int height = 29;
        const int coords[] = {
            // Top, bottom, left, right
            355,
            355 - height,
            171,
            171 + width,
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
    case CursorType::ArrowDown: {
        const int width = 28;
        const int height = 29;
        const int coords[] = {
            // Top, bottom, left, right
            323,
            323 - height,
            168,
            168 + width,
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::RotateLargeCounterclockwise: {
        const int width = 32;
        const int height = 46;
        const int coords[] = {
            357,
            357 - height,
            262,
            262 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::RotateLargeClockwise: {
        const int width = 32;
        const int height = 46;
        const int coords[] = {
            357,
            357 - height,
            294,
            294 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::RotateMediumCounterclockwise: {
        const int width = 30;
        const int height = 36;
        const int coords[] = {
            327,
            327 - height,
            200,
            200 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::RotateMediumClockwise: {
        const int width = 31;
        const int height = 36;
        const int coords[] = {
            327,
            327 - height,
            230,
            230 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::RotateSmallCounterclockwise: {
        const int width = 30;
        const int height = 27;
        const int coords[] = {
            358,
            358 - height,
            200,
            200 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::RotateSmallClockwise: {
        const int width = 30;
        const int height = 27;
        const int coords[] = {
            358,
            358 - height,
            230,
            230 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::ResizeHorizontal: {
        const int width = 30;
        const int height = 32;
        const int coords[] = {
            357,
            357 - height,
            424,
            424 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::ResizeVertical: {
        const int width = 30;
        const int height = 32;
        const int coords[] = {
            357,
            357 - height,
            456,
            456 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::MoveHorizontal: {
        const int width = 64;
        const int height = 18;
        const int coords[] = {
            309,
            309 - height,
            262,
            262 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::MoveVertical: {
        const int width = 19;
        const int height = 48;
        const int coords[] = {
            357,
            357 - height,
            487,
            487 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::Move: {
        const int width = 40;
        const int height = 40;
        const int coords[] = {
            290,
            290 - height,
            199,
            199 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::HandOpen: {
        const int width = 30;
        const int height = 32;
        const int coords[] = {
            323,
            323 - height,
            328,
            328 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::HandPointing: {
        const int width = 30;
        const int height = 32;
        const int coords[] = {
            357,
            357 - height,
            328,
            328 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::HandClosed: {
        const int width = 30;
        const int height = 32;
        const int coords[] = {
            323,
            323 - height,
            360,
            360 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::SmallCircle: {
        const int width = 30;
        const int height = 32;
        const int coords[] = {
            357,
            357 - height,
            360,
            360 + width
        };
        GLfloat ratios[8];
        createTextureCoordinates(coords, ratios);
        return Cursor(interfaceTextureId, width, height, ratios);
    }
        
    case CursorType::Default:
        throw std::invalid_argument("The Default cursor type indicates no custom cursor. It is not possible to create a custom cursor based on it.");
    default:
        throw std::invalid_argument("Cursor type not yet supported");
    }
}

void CursorManager::createTextureCoordinates(const int* pixelBtrl, GLfloat* outCoords) {
    constexpr int TOP = 1;
    constexpr int BOTTOM = 0;
    constexpr int LEFT = 3;
    constexpr int RIGHT = 2;
    
    const GLfloat top = GLfloat(pixelBtrl[TOP]) / INTERFACE_HEIGHT;
    const GLfloat bottom = GLfloat(pixelBtrl[BOTTOM]) / INTERFACE_HEIGHT;
    const GLfloat left = GLfloat(pixelBtrl[LEFT]) / INTERFACE_WIDTH;
    const GLfloat right = GLfloat(pixelBtrl[RIGHT]) / INTERFACE_WIDTH;
    
    /*
     * Output:
     * { left, top,
     * right, top,
     * right, bottom,
     * left, bottom }
     */
    outCoords[0] = left;
    outCoords[1] = top;
    outCoords[2] = right;
    outCoords[3] = top;
    outCoords[4] = right;
    outCoords[5] = bottom;
    outCoords[6] = left;
    outCoords[7] = bottom;
}

}
