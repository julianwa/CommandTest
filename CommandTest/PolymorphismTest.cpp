//
//  PolymorphismTest.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/25/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include "CommandReceiver.h"
#include "CommandReceiverImpl.hpp"

class BaseClass : public virtual CommandReceiver<BaseClass>
{
    
};