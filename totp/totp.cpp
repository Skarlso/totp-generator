// Copyright [2016 - *] <Gergely Brautigam>
#include "generator.hpp"
#include <ctime>
#include <cstdlib>
#include <string>
#include "commands/AddCommand.hpp"
#include "commands/DeleteCommand.hpp"
#include "commands/GenerateCommand.hpp"
#include "commands/HelpCommand.hpp"
#include <Commander/CommandRegistry.hpp>

using std::string;

int main(int argc, const char *argv[])
{
    Commander::CommandRegistry* registry = new Commander::CommandRegistry(argc, argv);
    registry->Register(&(Commands::NewAddCommand));
    registry->Register(&(Commands::NewDeleteCommand));
    registry->Register(&(Commands::NewGenerateCommand));
    registry->Register(&(Commands::NewHelpCommand));
    registry->Execute();
    return 0;
}
