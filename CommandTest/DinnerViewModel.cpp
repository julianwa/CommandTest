//
//  DinnerViewModel.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include "DinnerViewModel.h"
#include "ViewModelImpl.hpp"

using namespace std;

class DinnerViewModelImpl
: public virtual DinnerViewModel
, public virtual ViewModelImpl<DinnerViewModelImpl>
{
public:
    
#pragma mark - BlockMode
    
    ViewModelBlockMode BlockModeForCommandType(type_index type)
    {
        if (type == typeid(DineCommand)) {
            return ViewModelBlockMode::Edit;
        } else {
            return ViewModelBlockMode::None;
        }
    }
    
#pragma mark - SetTableCommand
    
    void HandleExecute(const shared_ptr<SetTableCommand> &command)
    {
        printf("  Set the table for dinner\n");
    }
    
#pragma mark - DineCommand
    
    void HandleBegin(const shared_ptr<DineCommand> &command)
    {
        printf("  Beginning dinner\n");
    }
    
    void HandleEnd(const shared_ptr<DineCommand> &command)
    {
        printf("  Dinner finished. The %s was lovely.\n", command->MainCourse.c_str());
    }
    
    void HandleCancel(const shared_ptr<DineCommand> &command)
    {
        printf("  Dinner ended early. We'll save the %s for later.\n", command->MainCourse.c_str());
    }
};

#pragma mark - CommandReceiveImpl

COMMAND_RECEIVER_IMPL(DinnerViewModel)

#pragma mark - Factory

shared_ptr<DinnerViewModel> DinnerViewModel::New()
{
    return make_shared<DinnerViewModelImpl>();
}
