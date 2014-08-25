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

#ifndef EXTERNALCOMMAND_H
#define EXTERNALCOMMAND_H
#include "namespaces.h"
#include <string>
#include <stdexcept>
#include <XPLMUtilities.h>

namespace PPLNAMESPACE {

/**
 * @brief The ExternalCommand class provides an interface for code
 * to trigger an X-Plane command that has been created somewhere else.
 */
class ExternalCommand
{
public:
    
    /**
      * A generic base exception that is thrown when anything
      * with looking up an X-Plane command and binding it goes wrong
      */
    class LookupException : public std::runtime_error {
    public:
        LookupException(const std::string& msg):
                runtime_error(msg)
        {}
    };
    
    /**
      * The command identifier could not be found in the plugin system's table
      * of commands, neither X-Plane nor a plugin publishes it.
      */
    class NotFoundException : public LookupException {
    public:
        NotFoundException(const std::string& msg):
                LookupException(msg)
        {}
    };
    
    /**
     * @brief Looks up a command
     * @param commandName The command name to look up
     * @throw NotFoundException If the commmand was not found
     */
    ExternalCommand(const std::string& commandName);
    
    /**
     * @brief Begins executing the command.
     * The command will continue until end() is called.
     * @see XPLMCommandBegin
     */
    void begin();
    
    /**
     * @brief Ends executing a command.
     * Used after begin().
     * @see XPLMCommandEnd
     */
    void end();
    
    /**
     * @brief Starts an then immediately stops the command.
     * @see XPLMCommandOnce
     */
    void trigger();
    
private:
    
    XPLMCommandRef commandRef;
    
};

}
#endif // EXTERNALCOMMAND_H
