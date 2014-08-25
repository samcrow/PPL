#ifndef VIEWCOMPONENT_H
#define VIEWCOMPONENT_H

#include "../../namespaces.h"
#include "drawable.h"

namespace PPLNAMESPACE {


/**
 * @brief A component, used from a View, that
 * draws something for a particular configuration using data
 * from a Model
 */
template < class ModelType >
class ViewComponent : public Drawable
{
public:
    ViewComponent(ModelType& model) :
        model_(model)
    {}
    
    ModelType& model() {
        return model_;
    }
    
private:
    ModelType& model_;
};

}
#endif // VIEWCOMPONENT_H
