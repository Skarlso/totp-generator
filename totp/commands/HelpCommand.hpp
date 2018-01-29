#ifndef _HelpCommand_hpp_
#define _HelpCommand_hpp_

#include <string>
#include <Commander/Command.hpp>
#include <Commander/CommandDescriptor.hpp>
#include <Commander/ArgumentRegistry.hpp>


namespace Commands {
    class HelpCommand : public Commander::Command {
        void Execute(Commander::ArgumentRegistry* args);
    };

    Commander::CommandDescriptor* NewHelpCommand(const std::string appName);
}

#endif
