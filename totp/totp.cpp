// Copyright [2016] <Gergely Brautigam>
#include "generator.hpp"
#include <ctime>
#include <cstdlib>
#include <string>
#include "commands/AddCommand.hpp"
#include "commands/GenerateCommand.hpp"
#include <Commander/CommandRegistry.hpp>

using std::string;

int main(int argc, const char *argv[])
{
    // Use the command library from Yitsushi?
    // command -> create
    // command -> generate
    // command -> delete

    Commander::CommandRegistry* registry = new Commander::CommandRegistry(argc, argv);
    registry->Register(&(Commands::NewAddCommand));
    registry->Register(&(Commands::NewGenerateCommand));
    registry->Execute();
    return 0;
}
