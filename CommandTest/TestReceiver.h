//
//  DinnerViewModel.h
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#include "CommandReceiver.h"
#include "TestCommands.h"

class TestReceiver
: public virtual CommandReceiver<TestReceiver>
{
public:
    
    using Commands = CommandSet<TestCommand>;
    using ContinuousCommands = CommandSet<>;
    
    static std::shared_ptr<TestReceiver> New();
};
