//
//  main.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include <iostream>
#include "Model.h"

using namespace std;

class GenericCommandReceiver
{
public:
    
    template<typename ReceiverT>
    GenericCommandReceiver(const shared_ptr<ReceiverT> &receiver)
    {
        _Self = make_shared<ReceiverWrapper<ReceiverT>>(receiver);
    }
    
    template<typename CommandT>
    void Execute(const shared_ptr<CommandT> &command)
    {
        _Self->Execute(command);
    }
private:
    struct Concept {
        virtual ~Concept() = default;
        
        template<typename CommandT>
        void Execute(const shared_ptr<CommandT> &command) const;
    };
    template <typename ReceiverT>
    struct ReceiverWrapper : Concept {
        ReceiverWrapper(const shared_ptr<ReceiverT> &receiver) : _Receiver(receiver) {}
        
        template<typename CommandT>
        void Execute(const shared_ptr<CommandT> &command)
        {
            _Receiver->Execute(command);
        }
        
        shared_ptr<ReceiverT> _Receiver;
    };
    shared_ptr<const Concept> _Self;
};

int main(int argc, const char * argv[])
{
    auto user = User::New(1);
    auto space = Space::New(3);
    
    vector<std::shared_ptr<Command>> commands = {
        make_shared<InsertSpace>(1, 2),
        make_shared<InsertSpace>(1, 3),
        make_shared<InsertIdea>(3, 4)
    };
    
    vector<GenericCommandReceiver> commandReceivers = {
        GenericCommandReceiver(user),
        GenericCommandReceiver(space)
    };
    
    for (auto receiver : commandReceivers) {
        for (auto command : commands) {
            receiver.Execute(command);
        }
    }

    return 0;
}
