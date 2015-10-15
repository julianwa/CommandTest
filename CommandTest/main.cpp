//
//  main.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include <iostream>
#include "TestReceiver.h"

using namespace std;

int main(int argc, const char * argv[])
{
    auto receiver = TestReceiver::New();
    auto command = make_shared<TestCommand>("this is a test");
    receiver->Execute(command);
    
    return 0;
}
