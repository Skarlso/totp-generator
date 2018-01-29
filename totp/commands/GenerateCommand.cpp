#include <iostream>
#include <string>
#include <Commander/ArgumentRegistry.hpp>
#include <Commander/CommandDescriptor.hpp>
#include "GenerateCommand.hpp"
#include "../generator.hpp"
#include "../accounting.hpp"

namespace Commands {
    void GenerateCommand::Execute(Commander::ArgumentRegistry* args)
    {
        std::string account = args->SubCommand();
        if (account.empty()) {
            printf("Please provide an account in the format of namespace.account.");
            return;
        }
        Accounting::Accounting* accounting = new Accounting::Accounting();
        std::string token = accounting->retrieveToken(account);
        if (token.empty()) {
            printf("Could not find token for account: %s\n", account.c_str());
            return;
        }

        TokenGenerator tg;
        std::time_t timer = std::time(nullptr);
        tg.generateOTPToken(token, timer);
    }

    Commander::CommandDescriptor* NewGenerateCommand(const std::string appName)
    {
        Commander::CommandDescriptor* desc;

        desc = new Commander::CommandDescriptor("generate", new GenerateCommand());

        return desc;
    }
}
