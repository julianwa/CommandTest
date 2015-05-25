//
//  CommandReceiverImpl.h
//  CommandTest
//
//  Created by Julian Walker on 5/20/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#include "Command.h"
#include <memory>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <boost/mpl/assert.hpp>

class CommandReceiverImpl : public std::enable_shared_from_this<CommandReceiverImpl>
{
public:
    using ExecutingCommands = std::unordered_map<std::type_index, std::shared_ptr<ContinuousCommand>>;
    
    virtual void ExecutingCommandsDidChange(const ExecutingCommands &executingCommands) {}
    
private:
    ExecutingCommands _ExecutingCommands;
    
public:
    template<class CommandReceiverT, class CommandT>
    void ExecuteImpl(const std::shared_ptr<CommandT> &command)
    {
        // If this assert is failing, that means someone is calling Execute on a CommandReceiver using a
        // Commnad that does not appear the in receiver's Commands set.
        BOOST_MPL_ASSERT((boost::mpl::has_key<typename CommandReceiverT::Commands, CommandT>));
        dynamic_cast<CommandReceiverT *>(this)->Execute(command);
    }
    
    template<class CommandReceiverT, class CommandT>
    void BeginImpl(const std::shared_ptr<CommandT> &command)
    {
        // If this assert is failing, that means someone is calling Begin on a CommandReceiver using a
        // Continuous Command that does not appear the in receiver's ContinuousCommands set.
        BOOST_MPL_ASSERT((boost::mpl::has_key<typename CommandReceiverT::ContinuousCommands, CommandT>));
        
        auto receiver = std::dynamic_pointer_cast<CommandReceiverT>(shared_from_this());
        
        std::weak_ptr<CommandReceiverT> weakReceiver = receiver;
        std::weak_ptr<CommandT> weakCommand = command;
        
        // Wire up the End method
        command->End = [weakReceiver, weakCommand] {
            auto receiver = weakReceiver.lock();
            auto command = weakCommand.lock();
            if (receiver && command) {
                receiver->End(command);
                
                command->SetWasEnded();
                receiver->_ExecutingCommands.erase(typeid(*command));
                receiver->ExecutingCommandsDidChange(receiver->_ExecutingCommands);
            }
        };
        
        // Wire up the Cancel method
        command->Cancel = [weakReceiver, weakCommand] {
            auto receiver = weakReceiver.lock();
            auto command = weakCommand.lock();
            if (receiver && command) {
                receiver->Cancel(command);
                
                command->SetWasCancelled();
                receiver->_ExecutingCommands.erase(typeid(*command));
                receiver->ExecutingCommandsDidChange(receiver->_ExecutingCommands);
            }
        };
        
        receiver->Begin(command);
        
        command->SetWasBegan();
        receiver->_ExecutingCommands[typeid(*command)] = std::static_pointer_cast<ContinuousCommand>(command);
        receiver->ExecutingCommandsDidChange(receiver->_ExecutingCommands);
    }
};


