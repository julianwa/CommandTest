//
//  ViewModel.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include "ViewModel.h"
#include "CommandReceiverImpl.hpp"

using namespace std;

template<class T>
class ViewModelImpl
: public virtual ViewModel
, public virtual CommandReceiverImpl
{
    ViewModelBlockMode _BlockMode;
    
public:
    
    ViewModelImpl()
    : _BlockMode(None)
    {
    }
    
    ViewModelBlockMode BlockMode() override
    {
        return _BlockMode;
    }
    
    void ExecutingCommandsDidChange(const CommandReceiverImpl::ExecutingCommands &executingCommands)
    {
        auto viewModel = dynamic_pointer_cast<T>(shared_from_this());
        ViewModelBlockMode result = ViewModelBlockMode::None;
        for (auto commandEntry : executingCommands) {
            auto mode = viewModel->BlockModeForCommandType(commandEntry.first);
            if (mode > result) {
                result = mode;
            }
        }
        _BlockMode = result;
    }

};