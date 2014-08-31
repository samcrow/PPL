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
    
    const std::string& name() const {
        return controllerName_;
    }
    
    virtual ~Controller() = default;
    
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

/**
 * A specialization of Controller for controllers
 * that do not require models
 */
template<>
class Controller<void>
{
public:  
    
    Controller(const std::string& name) :
        controllerName_(name)
    {
        
    }
    
    const std::string& name() const {
        return controllerName_;
    }
    
    virtual ~Controller() = default;
    
private:
    
    const std::string controllerName_;
    
};

}
#endif // CONTROLLER_H
