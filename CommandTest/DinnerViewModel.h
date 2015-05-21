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

class DinnerViewModel : public virtual ViewModel
{
public:
    
    using Commands = boost::mpl::set<SetTableCommand>;
    
    template<class T>
    void Execute(const std::shared_ptr<T> &command);
    
    template<class T>
    void Begin(const std::shared_ptr<T> &command);
    
    static std::shared_ptr<DinnerViewModel> New();
};
