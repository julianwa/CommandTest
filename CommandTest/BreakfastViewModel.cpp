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
, public virtual ViewModelImpl<BreakfastViewModelImpl>
{
public:
    
#pragma mark - BlockMode
    
    ViewModelBlockMode BlockModeForCommandType(type_index type)
    {
        return ViewModelBlockMode::None;
    }
    
#pragma mark -
    
    void HandleExecute(const shared_ptr<SetTableCommand> &command)
    {
        printf("Set the table for breakfast\n");
    }
};

#pragma mark - CommandReceiveImpl

COMMAND_RECEIVER_IMPL(BreakfastViewModel)

#pragma mark - Factory

shared_ptr<BreakfastViewModel> BreakfastViewModel::New()
{
    return make_shared<BreakfastViewModelImpl>();
}
