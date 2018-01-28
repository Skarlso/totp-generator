#ifndef _AddCommand_hpp_
#define _AddCommand_hpp_

#include <string>
#include <Commander/Command.hpp>
#include <Commander/CommandDescriptor.hpp>
#include <Commander/ArgumentRegistry.hpp>


namespace Commands {
  class AddCommand : public Commander::Command {
    void Execute(Commander::ArgumentRegistry* args);
  };

  Commander::CommandDescriptor* NewAddCommand(const std::string appName);
}

#endif