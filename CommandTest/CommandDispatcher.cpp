//
//  CommandDispatcher.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/20/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include "CommandDispatcher.h"

using namespace std;

shared_ptr<CommandDispatcher> CommandDispatcher::GlobalDispatcher()
{
    static shared_ptr<CommandDispatcher> instance;
    if (!instance) {
        instance = shared_ptr<CommandDispatcher>(new CommandDispatcher());
    }
    return instance;
}
