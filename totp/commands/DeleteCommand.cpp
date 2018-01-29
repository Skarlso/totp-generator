#include <iostream>
#include <string>
#include <Commander/ArgumentRegistry.hpp>
#include <Commander/CommandDescriptor.hpp>
#include "DeleteCommand.hpp"
#include "../accounting.hpp"

namespace Commands {
    void DeleteCommand::Execute(Commander::ArgumentRegistry* args)
    {
        std::string account = args->SubCommand();
        if (account.empty()) {
            printf("Please provide an account to delete.");
            return;
        }

        Accounting::Accounting* acc = new Accounting::Accounting();
        acc->deleteAccount(account);
    }

    Commander::CommandDescriptor* NewDeleteCommand(const std::string appName)
    {
        Commander::CommandDescriptor* desc;

        desc = new Commander::CommandDescriptor("delete", new DeleteCommand());

        return desc;
    }
}