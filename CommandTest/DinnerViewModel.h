//
//  DinnerViewModel.h
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#include "ViewModel.h"
#include <boost/mpl/set.hpp>
#include "MealCommands.h"
#include "CommandReceiver.h"

class DinnerViewModel
: public virtual ViewModel
, public virtual CommandReceiver<DinnerViewModel>
{
public:
    
    using Commands = boost::mpl::set<SetTableCommand>;
    
    static std::shared_ptr<DinnerViewModel> New();
};
