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

#ifndef CLICKREGION_H
#define CLICKREGION_H

#include "../../../namespaces.h"
#include "../../../ui/cursortype.h"
#include <boost/signals2.hpp>

namespace PPLNAMESPACE {

/**
 * @brief A region that the user can click on
 */
class ClickRegion
{
public:
    ClickRegion(int top, int left, int bottom, int right, CursorType type = CursorType::HandPointing);
    
    ClickRegion();
    
    typedef boost::signals2::signal<void ()> signal_type;
    typedef signal_type::slot_type slot_type;
    
    /**
     * @brief Adds a slot to be notified when the user clicks on this region
     * @param handler
     * @return 
     */
    boost::signals2::connection addClickHandler(slot_type handler);
    
    /**
     * @brief Checks if the given coordinates are within this region,
     * and notifies listeners if it is.
     * @param x
     * @param y
     * @return True if the coordinates are within this region, otherwise false
     */
    bool checkForClick(int x, int y);
    
    
    bool isInRegion(int x, int y);
    
    // Location accessors
    inline float top() const {
        return top_;
    }
    inline float left() const {
        return left_;
    }
    inline float bottom() const {
        return bottom_;
    }
    inline float right() const {
        return right_;
    }
    
    inline CursorType cursorType() const {
        return cursorType_;
    }
    
private:
    int top_;
    int left_;
    int bottom_;
    int right_;
    
    CursorType cursorType_;
    
    /**
     * @brief A signal emitted when this region is clicked on
     */
    signal_type clicked;
    
};

}
#endif // CLICKREGION_H
