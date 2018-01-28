#include <iostream>
#include <string>
#include <Commander/ArgumentRegistry.hpp>
#include <Commander/CommandDescriptor.hpp>
#include "AddCommand.hpp"
#include "../accounting.hpp"

namespace Commands {
    void AddCommand::Execute(Commander::ArgumentRegistry* args)
    {
        std::string account = args->SubCommand();
        if (account.empty()) {
            printf("Please provide an account in the format of namespace.account.");
            return;
        }
        Accounting::Accounting* acc = new Accounting::Accounting();
        std::cout << "Adding new totp token" << std::endl;
    }

    Commander::CommandDescriptor* NewAddCommand(const std::string appName)
    {
        Commander::CommandDescriptor* desc;

        desc = new Commander::CommandDescriptor("add", new AddCommand());

        return desc;
    }
}