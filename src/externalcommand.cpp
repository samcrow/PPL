#include "externalcommand.h"

namespace PPLNAMESPACE {

ExternalCommand::ExternalCommand(const std::string& commandName) :
    commandRef(XPLMFindCommand(commandName.c_str()))
{
    if(commandRef == 0) {
        throw NotFoundException("Command "+commandName+" was not found");
    }
}

void ExternalCommand::begin() {
    XPLMCommandBegin(commandRef);
}

void ExternalCommand::end() {
    XPLMCommandEnd(commandRef);
}

void ExternalCommand::trigger() {
    XPLMCommandOnce(commandRef);
}

}
