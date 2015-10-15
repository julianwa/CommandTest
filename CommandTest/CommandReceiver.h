//
//  CommandReceiver.hpp
//  CommandTest
//
//  Created by Julian Walker on 5/20/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#import <memory>
#include <boost/mpl/set.hpp>

template<class ReceiverT>
class CommandReceiver
{
public:
    
    template <typename... Args>
    using CommandSet = boost::mpl::set<Args...>;
    
    virtual ~CommandReceiver() {}
    
    template<class T>
    void Execute(const std::shared_ptr<T> &command);

    template<class T>
    void Begin(const std::shared_ptr<T> &command);
};