#ifndef _DeleteCommand_hpp_
#define _DeleteCommand_hpp_

#include <string>
#include <Commander/Command.hpp>
#include <Commander/CommandDescriptor.hpp>
#include <Commander/ArgumentRegistry.hpp>


namespace Commands {
    class DeleteCommand : public Commander::Command {
        void Execute(Commander::ArgumentRegistry* args);
    };

    Commander::CommandDescriptor* NewDeleteCommand(const std::string appName);
}

#endif
