#ifndef CURSORMANAGER_H
#define CURSORMANAGER_H
#include <memory>
#include "../namespaces.h"
#include "../mvc/view/drawable.h"
#include <boost/noncopyable.hpp>
#include <unordered_map>
#include "cursortype.h"
#include "cursor.h"

namespace PPLNAMESPACE {

/**
 * @brief The CursorManager class provides access to
 * cursors provided by X-Plane's interface image file
 */
class CursorManager : public boost::noncopyable
{
public:
    // Static
    static CursorManager& getInstance();
    
    
    
    // Non-static
    
    /**
     * @brief Returns a reference to a cursor of the requested type
     * @param type The cursor type to get. This must not be CusorType::Default.
     * @return 
     */
    Cursor& getCursor(CursorType type);
    
private:
    
    // Non-static
    
    CursorManager();
    
    std::unordered_map<CursorType, Cursor> cache;
    
    int interfaceTextureId;
    
    Cursor createCursor(CursorType type);
    
    /**
     * @brief Converts from pixel coordinates in the interface bitmap to coordinate
     * ratios
     * @param pixelTblr A 4-element array (bottom, top, right, left) of the pixel coordinates
     * of the area
     * @param outCoords An 8-element array of output coordinate ratios:
     * { left, top,
     * right, top,
     * right, bottom,
     * left, bottom }
     */
    void createTextureCoordinates(const int* pixelBtrl, GLfloat* outCoords);
    
    // Static
    static std::unique_ptr<CursorManager> instance_ptr;
};


}
#endif // CURSORMANAGER_H
