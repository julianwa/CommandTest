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

int main(int argc, const char * argv[])
{
    auto user = User::New(1);
    
    vector<std::shared_ptr<Command>> commands = {
        make_shared<InsertSpace>(1, 2),
        make_shared<InsertSpace>(1, 3),
        make_shared<InsertIdea>(3, 4)
    };
    
    for (auto command : commands) {
        user->Execute(command);
    }

    return 0;
}
