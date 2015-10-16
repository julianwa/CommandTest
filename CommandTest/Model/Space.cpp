//
//  Space.cpp
//  CommandTest
//
//  Created by Julian Walker on 10/15/15.
//  Copyright © 2015 Julian Walker. All rights reserved.
//

#include "Space.h"
#include "CommandReceiverImpl.hpp"

using namespace std;

class SpaceImpl
: public virtual Space
, public CommandReceiverImpl
{
    const int Id;
    
public:
    
    SpaceImpl(int id) : Id(id) {}
    
#pragma mark - InsertSpace
    
    void HandleExecute(const shared_ptr<InsertIdea> &command)
    {
        assert(0);
    }
};

#pragma mark - CommandReceiverImpl

COMMAND_RECEIVER_IMPL(Space)

#pragma mark - Factory

shared_ptr<Space> Space::New(int id)
{
    return make_shared<SpaceImpl>(id);
}
