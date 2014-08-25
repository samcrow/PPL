#include "signalcommand.h"

namespace PPLNAMESPACE {

SignalCommand::SignalCommand(const char *inName, const char *inDescription, int inBefore) :
    Command(inName, inDescription, inBefore)
{
}

int SignalCommand::handler(XPLMCommandRef, XPLMCommandPhase inPhase)
{
    // Only trigger the listener if this command is starting
    if(inPhase == xplm_CommandBegin) {
        signal();
    }
    return 1;
}

boost::signals2::connection SignalCommand::addListener(slot_type slot) {
    return signal.connect(slot);
}

}
