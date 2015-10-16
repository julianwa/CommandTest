//
//  Space.hpp
//  CommandTest
//
//  Created by Julian Walker on 10/15/15.
//  Copyright © 2015 Julian Walker. All rights reserved.
//

#pragma once

#include "ModelCommands.h"
#include "CommandReceiver.h"
#include <memory>
#include <vector>

class Space
: public virtual CommandReceiver<Space>
{
protected:
    ~Space() {}
public:
    using Commands = CommandSet<InsertIdea>;
    using ContinuousCommands = CommandSet<>;
    
    static std::shared_ptr<Space> New(int id);
};
