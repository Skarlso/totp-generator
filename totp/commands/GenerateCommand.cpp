#include <iostream>
#include <string>
#include <Commander/ArgumentRegistry.hpp>
#include <Commander/CommandDescriptor.hpp>
#include "GenerateCommand.hpp"
#include "../generator.hpp"

namespace Commands {
    void GenerateCommand::Execute(Commander::ArgumentRegistry* args)
    {
        TokenGenerator tg;
        std::time_t timer = std::time(nullptr);
        if(const char* env_p = std::getenv("OTP_TOKEN")) {
            string token(env_p);
            tg.generateOTPToken(token, timer);
        } else {
            printf("Please set your environment property 'OTP_TOKEN' to your token key.\n");
        }
    }

    Commander::CommandDescriptor* NewGenerateCommand(const std::string appName)
    {
        Commander::CommandDescriptor* desc;

        desc = new Commander::CommandDescriptor("generate", new GenerateCommand());

        return desc;
    }
}