#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>
#include "../namespaces.h"

namespace PPLNAMESPACE {

/**
 * @brief A controller handles the logic of a particular subsystem.
 */
template < class ModelType >
class Controller
{
public:
    Controller(std::string name, ModelType& model) :
        controllerName_(name),
        model_(model)
    {}
    
    /**
     * @brief Sets the model to be used by this controller
     * @param newModel
     */
    void setModel(ModelType& newModel) {
        model_ = newModel;
    }
    
    virtual ~Controller() {
        
    }
    
protected:
    /**
     * @brief Returns a pointer to the model currently in use by this controller
     * @return 
     */
    inline ModelType& model() {
        return model_;
    }
    
private:
    
    const std::string controllerName_;
    ModelType& model_;
    
};

}
#endif // CONTROLLER_H
