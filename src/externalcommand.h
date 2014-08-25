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
