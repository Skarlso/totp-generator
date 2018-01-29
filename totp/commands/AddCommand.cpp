#include <iostream>
#include <string>
#include <Commander/ArgumentRegistry.hpp>
#include <Commander/CommandDescriptor.hpp>
#include "AddCommand.hpp"
#include "../accounting.hpp"

namespace Commands {
    void AddCommand::Execute(Commander::ArgumentRegistry* args)
    {
        std::string account;
        std::string token;
        std::cout << "account:";
        std::cin >> account;
        std::cout << "token:";
        std::cin >> token;

        Accounting::Accounting* acc = new Accounting::Accounting();
        acc->saveToken(account, token);
    }

    Commander::CommandDescriptor* NewAddCommand(const std::string appName)
    {
        Commander::CommandDescriptor* desc;

        desc = new Commander::CommandDescriptor("add", new AddCommand());

        return desc;
    }
}
