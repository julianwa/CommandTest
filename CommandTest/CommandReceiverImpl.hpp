//
//  CommandReceiverImpl.h
//  CommandTest
//
//  Created by Julian Walker on 5/20/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#include <typeindex>
#include <unordered_map>
#include <boost/mpl/for_each.hpp>
#include "Command.h"

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
        dynamic_cast<CommandReceiverT *>(this)->HandleExecute(command);
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
                receiver->HandleEnd(command);
                
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
                receiver->HandleCancel(command);
                
                command->SetWasCancelled();
                receiver->_ExecutingCommands.erase(typeid(*command));
                receiver->ExecutingCommandsDidChange(receiver->_ExecutingCommands);
            }
        };
        
        receiver->HandleBegin(command);
        
        command->SetWasBegan();
        receiver->_ExecutingCommands[typeid(*command)] = std::static_pointer_cast<ContinuousCommand>(command);
        receiver->ExecutingCommandsDidChange(receiver->_ExecutingCommands);
    }
};

#pragma mark - Template Instantiations

template<class T, typename B, typename E>
struct InstantiateCommandFunctions
{
    InstantiateCommandFunctions()
    {
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wunused-value"
        &T::template CommandReceiver<T>::template Execute<typename B::type>;
        #pragma clang diagnostic pop
    }
    
    InstantiateCommandFunctions<T, typename boost::mpl::next<B>::type, E> next;
};
template<class T, typename E>
struct InstantiateCommandFunctions<T, E, E> {};

template<class T, typename B, typename E>
struct InstantiateContinuousCommandFunctions
{
    InstantiateContinuousCommandFunctions()
    {
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wunused-value"
        &T::template CommandReceiver<T>::template Begin<typename B::type>;
        #pragma clang diagnostic pop
    }
    
    InstantiateCommandFunctions<T, typename boost::mpl::next<B>::type, E> next;
};
template<class T, typename E>
struct InstantiateContinuousCommandFunctions<T, E, E> {};

template<class T>
void InstantiateCommandReceiverFunctions()
{
    InstantiateCommandFunctions<T
    , typename boost::mpl::begin<typename T::Commands>::type
    , typename boost::mpl::end<typename T::Commands>::type>();
    
    InstantiateContinuousCommandFunctions<T
    , typename boost::mpl::begin<typename T::ContinuousCommands>::type
    , typename boost::mpl::end<typename T::ContinuousCommands>::type>();
}

#pragma mark - 

#define COMMAND_RECEIVER_IMPL(CommandReceiverT)                                                     \
                                                                                                    \
template void InstantiateCommandReceiverFunctions<CommandReceiverT>();                              \
                                                                                                    \
template<>                                                                                          \
template<class T>                                                                                   \
void CommandReceiver<CommandReceiverT>::Execute(const shared_ptr<T> &command)                       \
{                                                                                                   \
    dynamic_cast<CommandReceiverImpl *>(this)->ExecuteImpl<CommandReceiverT##Impl, T>(command);     \
}                                                                                                   \
                                                                                                    \
template<>                                                                                          \
template<class T>                                                                                   \
void CommandReceiver<CommandReceiverT>::Begin(const shared_ptr<T> &command)                         \
{                                                                                                   \
    dynamic_cast<CommandReceiverImpl *>(this)->BeginImpl<CommandReceiverT##Impl, T>(command);       \
}                                                                                                   \


