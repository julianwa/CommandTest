//
//  DinnerViewModel.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include "TestReceiver.h"
#include "CommandReceiverImpl.hpp"

using namespace std;

class TestReceiverImpl
: public virtual TestReceiver
{
public:
    
#pragma mark - TestCommand
    
    void HandleExecute(const shared_ptr<TestCommand> &command)
    {
        printf("Message received: %s\n", command->Message.c_str());
    }
};

#pragma mark - CommandReceiveImpl

COMMAND_RECEIVER_IMPL(TestReceiver)

#pragma mark - Factory

shared_ptr<TestReceiver> TestReceiver::New()
{
    return make_shared<TestReceiverImpl>();
}
