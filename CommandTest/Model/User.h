//
//  User.hpp
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

class User
: public virtual CommandReceiver<User>
{
protected:
    ~User() {}
public:
    using Commands = CommandSet<InsertSpace>;
    using ContinuousCommands = CommandSet<>;
    
    virtual const std::vector<std::shared_ptr<class Space>> & Spaces() = 0;
    
    static std::shared_ptr<User> New(int id);
};
