//
//  BreakfastViewModel.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include "BreakfastViewModel.h"
#include "ViewModelImpl.hpp"
#include "MealCommands.h"

class BreakfastViewModelImpl
: public virtual BreakfastViewModel
, public virtual ViewModelImpl
{
public:
    
    string Name() override
    {
        return "Breakfast";
    }
    
    void Execute(const shared_ptr<SetTableCommand> &command)
    {
        printf("Set the table for breakfast\n");
    }
};

template void BreakfastViewModel::Execute<SetTableCommand>(const shared_ptr<SetTableCommand> &command);

template<class T>
void BreakfastViewModel::Execute(const shared_ptr<T> &command)
{
    dynamic_cast<ViewModelImpl *>(this)->ExecuteImpl<BreakfastViewModelImpl, T>(command);
}

shared_ptr<BreakfastViewModel> BreakfastViewModel::New()
{
    return make_shared<BreakfastViewModelImpl>();
}
