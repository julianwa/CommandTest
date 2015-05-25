//
//  DinnerViewModel.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include "DinnerViewModel.h"
#include "MealCommands.h"
#include "CommandReceiverImpl.hpp"
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
    
    void Execute(const shared_ptr<SetTableCommand> &command)
    {
        printf("Set the table for dinner\n");
    }
    
#pragma mark - DineCommand
    
    void Begin(const shared_ptr<DineCommand> &command)
    {
        printf("Beginning dinner\n");
    }
    
    void End(const shared_ptr<DineCommand> &command)
    {
        printf("Dinner finished. The %s was lovely.\n", command->MainCourse.c_str());
    }
    
    void Cancel(const shared_ptr<DineCommand> &command)
    {
        printf("Dinner ended early. Druncle at it again.\n");
    }
};

#pragma mark - Template Instantiations

template void DinnerViewModel::Begin<DineCommand>(const shared_ptr<DineCommand> &command);
template void DinnerViewModel::Execute<SetTableCommand>(const shared_ptr<SetTableCommand> &command);

#pragma mark - Proxy to CommandReceiverImpl

template<>
template<class T>
void CommandReceiver<DinnerViewModel>::Execute(const shared_ptr<T> &command)
{
    dynamic_cast<CommandReceiverImpl *>(this)->DinnerViewModelImpl::ExecuteImpl<DinnerViewModelImpl, T>(command);
}

template<>
template<class T>
void CommandReceiver<DinnerViewModel>::Begin(const shared_ptr<T> &command)
{
    dynamic_cast<CommandReceiverImpl *>(this)->BeginImpl<DinnerViewModelImpl, T>(command);
}

#pragma mark - Factory

shared_ptr<DinnerViewModel> DinnerViewModel::New()
{
    return make_shared<DinnerViewModelImpl>();
}
