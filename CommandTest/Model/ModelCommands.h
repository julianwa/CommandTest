//
//  ModelCommands.h
//  CommandTest
//
//  Created by Julian Walker on 10/15/15.
//  Copyright © 2015 Julian Walker. All rights reserved.
//

#pragma once

#include "Command.h"
#include <string>

struct InsertSpace : public Command
{
    const int ContainerId;
    const int Id;
    
    InsertSpace()
    : ContainerId(0)
    , Id(0)
    {
    }
    
    InsertSpace(int containerId, int id)
    : ContainerId(containerId)
    , Id(id) {}
};

struct InsertIdea : public Command
{
    const int ContainerId;
    const int Id;
    
    InsertIdea()
    : ContainerId(0)
    , Id(0)
    {
    }
    
    InsertIdea(int containerId, int id)
    : ContainerId(containerId)
    , Id(id) {}
};

