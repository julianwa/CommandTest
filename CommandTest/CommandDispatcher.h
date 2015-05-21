//
//  CommandDispatcher.h
//  CommandTest
//
//  Created by Julian Walker on 5/19/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#include <functional>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <memory>

class CommandDispatcher
{
private:
    
    using Receiver = std::function<void (const std::shared_ptr<class Command> &command)>;
    using ReceiverVector = std::vector<Receiver>;
    using ReceiverVectorPtr = std::shared_ptr<ReceiverVector>;
    std::unordered_map<std::type_index, ReceiverVectorPtr> _Receivers;
    
protected:
    
    CommandDispatcher() {}
    
public:
    template <class CommandT, class ReceiverT>
    void RegisterReceiver(const std::shared_ptr<ReceiverT> receiver)
    {
        ReceiverVectorPtr receivers;
        auto it = _Receivers.find(typeid(CommandT));
        if (it == _Receivers.end()) {
            receivers = std::make_shared<ReceiverVector>();
            _Receivers[typeid(CommandT)] = receivers;
        } else {
            receivers = it->second;
        }
        
        std::weak_ptr<ReceiverT> weakReceiver = receiver;
        receivers->push_back([weakReceiver](const std::shared_ptr<class Command> &command) {
            auto strongReceiver = weakReceiver.lock();
            if (strongReceiver) {
                strongReceiver->Execute(std::dynamic_pointer_cast<CommandT>(command));
            }
        });
    }
    
    template <class CommandT>
    void Dispatch(const std::shared_ptr<CommandT> &command)
    {
        auto it = _Receivers.find(typeid(CommandT));
        if (it != _Receivers.end()) {
            auto receivers = it->second;
            for (auto &receiver : *receivers) {
                receiver(command);
            }
        }
    }
    
    static std::shared_ptr<CommandDispatcher> GlobalDispatcher();
};


