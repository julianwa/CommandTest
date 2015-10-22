//
//  main.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include <iostream>
#include "Model.h"

using namespace std;

template<class ReceiverT>
std::function<void(const shared_ptr<Command> &)> DeferCommandExecution(const std::shared_ptr<ReceiverT> receiver)
{
    return [receiver](const shared_ptr<Command> &command){
        receiver->Execute(command);
    };
};

int main(int argc, const char * argv[])
{
    auto user = User::New(1);
    auto space = Space::New(3);
    
    vector<std::shared_ptr<Command>> commands = {
        make_shared<InsertSpace>(1, 2),
        make_shared<InsertSpace>(1, 3),
        make_shared<InsertIdea>(3, 4)
    };
    
    auto executionQueue = {
        DeferCommandExecution(user),
        DeferCommandExecution(space)
    };
    
    // Execute all commands against all receivers. This doesn't make a ton a sense, but does demonstrate the
    // flexibility.
    for (auto execute : executionQueue) {
        for (auto command : commands) {
            execute(command);
        }
    }

    return 0;
}
