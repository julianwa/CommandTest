//
//  BreakfastViewModel.h
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#include "CommandReceiver.h"
#include "ViewModel.h"
#include "MealCommands.h"

class BreakfastViewModel
: public virtual ViewModel
, public virtual CommandReceiver<BreakfastViewModel>
{
public:
    
    using Commands = boost::mpl::set<SetTableCommand>;
    using ContinuousCommands = boost::mpl::set<>;
    
    static std::shared_ptr<BreakfastViewModel> New();
};