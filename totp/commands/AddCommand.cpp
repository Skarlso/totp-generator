#include <iostream>
#include <string>
#include <Commander/ArgumentRegistry.hpp>
#include <Commander/CommandDescriptor.hpp>
#include "AddCommand.hpp"

namespace Commands {
    void AddCommand::Execute(Commander::ArgumentRegistry* args)
    {
        std::cout << "Adding new totp token" << std::endl;
    }

    Commander::CommandDescriptor* NewAddCommand(const std::string appName)
    {
        Commander::CommandDescriptor* desc;

        desc = new Commander::CommandDescriptor("add", new AddCommand());

        return desc;
    }
}