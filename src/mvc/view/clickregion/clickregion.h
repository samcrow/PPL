#ifndef CLICKREGION_H
#define CLICKREGION_H

#include "../../../namespaces.h"
#include <boost/signals2.hpp>

namespace PPLNAMESPACE {

/**
 * @brief A region that the user can click on
 */
class ClickRegion
{
public:
    ClickRegion(int top, int left, int bottom, int right);
    
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
    
    // Location accessors
    float top() {
        return top_;
    }
    float left() {
        return left_;
    }
    float bottom() {
        return bottom_;
    }
    float right() {
        return right_;
    }
    
private:
    int top_;
    int left_;
    int bottom_;
    int right_;
    
    /**
     * @brief A signal emitted when this region is clicked on
     */
    signal_type clicked;
    
    bool isInRegion(int x, int y);
    
};

}
#endif // CLICKREGION_H
