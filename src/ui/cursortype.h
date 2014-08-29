#ifndef CURSORTYPE_H
#define CURSORTYPE_H
#include "../namespaces.h"
#include "../util/hash_specialization.h"

namespace PPLNAMESPACE {

enum class CursorType {
    
    /**
     * Indicates that the default cursor
     * should be used.
     */
    Default,
    
    /// An upwards-facing arrow
    ArrowUp,
    /// A downwards-facing arrow
    ArrowDown,
    
    RotateLargeCounterclockwise,
    RotateLargeClockwise,
    
    RotateMediumCounterclockwise,
    RotateMediumClockwise,
    
    RotateSmallCounterclockwise,
    RotateSmallClockwise,
    
    /// A cursor for resizing a vertical edge in a horizontal direction
    ResizeHorizontal,
    /// A cursor for resizing a horizontal edge in a vertical direction
    ResizeVertical,
    
    MoveHorizontal,
    MoveVertical,
    /// A cursor for moving in both vertical and horizontal directions
    Move,
    
    HandOpen,
    HandPointing,
    HandClosed,
    
    /// A small circle, used by X-Plane when the user is pressing a button
    SmallCircle,
    
};

}

HASH_SPECIALIZATION(PPLNAMESPACE::CursorType)

#endif // CURSORTYPE_H
