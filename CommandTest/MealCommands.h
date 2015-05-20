//
//  MealCommands.h
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#include "Command.h"

class SetTableCommand : public Command
{
};

class DineCommand : public ContinuousCommand
{
public:
    
    const std::string MainCourse;
    
    DineCommand(const std::string & mainCourse)
    : MainCourse(mainCourse)
    {
    }
};
