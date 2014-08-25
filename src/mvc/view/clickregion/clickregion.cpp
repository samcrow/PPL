#include "clickregion.h"

namespace PPLNAMESPACE {


ClickRegion::ClickRegion(int top, int left, int bottom, int right) :
    top_(top),
    left_(left),
    bottom_(bottom),
    right_(right)
{
}

    

bool ClickRegion::checkForClick(int x, int y) {
    if(isInRegion(x, y)) {
        clicked();
        return true;
    }
    else {
        return false;
    }
}

bool ClickRegion::isInRegion(int x, int y) {
    return x > left_ && x < right_ && y > bottom_ && y < top_;
}

boost::signals2::connection ClickRegion::addClickHandler(slot_type handler) {
    return clicked.connect(handler);
}

}
