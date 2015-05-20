//
//  ViewModel.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include "ViewModel.h"
#include "Command.h"
#include <map>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

using namespace std;

class ViewModelImpl
: public virtual ViewModel
, public std::enable_shared_from_this<ViewModelImpl>
{
    ViewModelBlockMode _BlockMode;
    unordered_map<std::type_index, shared_ptr<ContinuousCommand>> _CurrentCommands;
    
public:
    
    ViewModelImpl()
    : _BlockMode(None)
    {
    }
    
    ViewModelBlockMode BlockMode() override
    {
        return _BlockMode;
    }
    
    template <class ViewModelT>
    void UpdateBlockMode()
    {
        auto viewModel = dynamic_pointer_cast<ViewModelT>(shared_from_this());
        printf("Num executing commands: %zu\n", _CurrentCommands.size());
        ViewModelBlockMode result = ViewModelBlockMode::None;
        for (auto commandEntry : _CurrentCommands) {
            auto mode = viewModel->BlockModeForCommandType(commandEntry.first);
            if (mode > result) {
                result = mode;
            }
        }
        _BlockMode = result;
    }
    
    template<class ViewModelT, class CommandT>
    void ExecuteImpl(const shared_ptr<CommandT> &command)
    {
        dynamic_cast<ViewModelT *>(this)->Execute(command);
    }
    
    template<class ViewModelT, class CommandT>
    void BeginImpl(const shared_ptr<CommandT> &command)
    {
        auto viewModel = dynamic_pointer_cast<ViewModelT>(shared_from_this());

        weak_ptr<ViewModelT> weakViewModel = viewModel;
        weak_ptr<CommandT> weakCommand = command;
        
        // Wire up the End method
        command->End = [weakViewModel, weakCommand] {
            auto viewModel = weakViewModel.lock();
            auto command = weakCommand.lock();
            if (viewModel && command) {
                viewModel->End(command);
                
                command->SetWasEnded();
                viewModel->_CurrentCommands.erase(typeid(*command));
                viewModel->template UpdateBlockMode<ViewModelT>();
            }
        };
        
        // Wire up the Cancel method
        command->Cancel = [weakViewModel, weakCommand] {
            auto viewModel = weakViewModel.lock();
            auto command = weakCommand.lock();
            if (viewModel && command) {
                viewModel->Cancel(command);
        
                command->SetWasCancelled();
                viewModel->_CurrentCommands.erase(typeid(*command));
                viewModel->template UpdateBlockMode<ViewModelT>();
            }
        };
        
        viewModel->Begin(command);
        
        command->SetWasBegan();
        viewModel->_CurrentCommands[typeid(*command)] = static_pointer_cast<ContinuousCommand>(command);
        viewModel->template UpdateBlockMode<ViewModelT>();
    }
};