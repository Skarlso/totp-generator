#include <iostream>
#include <string>
#include <Commander/ArgumentRegistry.hpp>
#include <Commander/CommandDescriptor.hpp>
#include "HelpCommand.hpp"

namespace Commands {
    void HelpCommand::Execute(Commander::ArgumentRegistry* args)
    {
        std::cout <<
            "totp add # Follow the prompts to add a new token\n"
            "totp generate [account] # Generate a totp using the token defined for [account]\n"
            "totp delete [account] # Remove the account defined in [account]\n"
            "Examples:\n"
            "totp add # account:test | token:ASDFQWERZXCV= | Added token ASDFQWERZXCV= to account test.\n"
            "totp generate test # 123456\n"
            "totp generate test | pbcopy # Copies the otp directly to clipboard.\n"
            "totp delete test # Account test deleted.\n";
    }

    Commander::CommandDescriptor* NewHelpCommand(const std::string appName)
    {
        Commander::CommandDescriptor* desc;

        desc = new Commander::CommandDescriptor("help", new HelpCommand());

        return desc;
    }
}
