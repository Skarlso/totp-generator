#ifndef _GenerateCommand_hpp_
#define _GenerateCommand_hpp_

#include <string>
#include <Commander/Command.hpp>
#include <Commander/CommandDescriptor.hpp>
#include <Commander/ArgumentRegistry.hpp>


namespace Commands {
    class GenerateCommand : public Commander::Command {
        void Execute(Commander::ArgumentRegistry* args);
    };

    Commander::CommandDescriptor* NewGenerateCommand(const std::string appName);
}

#endif
