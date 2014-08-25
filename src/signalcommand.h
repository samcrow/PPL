#ifndef SIGNALCOMMAND_H
#define SIGNALCOMMAND_H
#include "namespaces.h"
#include "command.h"
#include <boost/signals2.hpp>

namespace PPLNAMESPACE {

/**
 * @brief The SignalCommand class is a type of command that emits a signal
 * when it is triggered.
 */
class SignalCommand : public Command
{
public:
    SignalCommand(const char *inName, const char *inDescription, int inBefore);
    
    virtual int handler(XPLMCommandRef, XPLMCommandPhase);
    
    typedef boost::signals2::signal<void ()> signal_type;
    typedef signal_type::slot_type slot_type;
    
    /**
     * @brief Connects a function to be called when this command is triggered
     * @param slot
     * @return 
     */
    boost::signals2::connection addListener(slot_type slot);
    
private:
    signal_type signal;
};

}
#endif // SIGNALCOMMAND_H
