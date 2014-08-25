#ifndef VIEW_H
#define VIEW_H
#include "../namespaces.h"
#include <type_traits>

namespace PPLNAMESPACE {

/**
 * @brief The View class displays graphics
 * based on information provided by a Drawable, which may also be a Controller.
 * 
 * A View interacts with a Controller and gets the ViewComponent
 * that should be used to represent the controller.
 * 
 */
template < class ControllerType >
class View
{
public:
    View(ControllerType& controller) :
        controller_(controller)
    {}
    
protected:
    ControllerType& controller() {
        return controller_;
    }
    
private:
    
    ControllerType& controller_;
    
};

}
#endif // VIEW_H
