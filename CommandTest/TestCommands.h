//
//  MealCommands.h
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#include "Command.h"
#include <string>

struct TestCommand : public Command
{
    const std::string Message;
    
    TestCommand() : Message("") {}

    TestCommand(std::string message) : Message(message) {}
};
