//
//  User.cpp
//  CommandTest
//
//  Created by Julian Walker on 10/15/15.
//  Copyright © 2015 Julian Walker. All rights reserved.
//

#include "User.h"
#include "Space.h"
#include "CommandReceiverImpl.hpp"

using namespace std;

class UserImpl
: public virtual User
, public CommandReceiverImpl
{
    vector<shared_ptr<Space>> _Spaces;
    
public:
    
    const vector<shared_ptr<Space>> & Spaces()
    {
        return _Spaces;
    }
    
#pragma mark - InsertSpace
    
    void HandleExecute(const shared_ptr<InsertSpace> &command)
    {
        printf("Insert space: %d\n", command->Id);
        _Spaces.push_back(Space::New(command->Id));
    }
};

#pragma mark - CommandReceiverImpl

COMMAND_RECEIVER_IMPL(User)

#pragma mark - Factory

shared_ptr<User> User::New(int id)
{
    return make_shared<UserImpl>();
}
