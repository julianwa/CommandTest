//
//  Command.h
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#include <functional>
#include <assert.h>

class Command
{
};

class ContinuousCommand
{
    bool _WasBegan;
    bool _WasCancelled;
    bool _WasEnded;
    
public:
    
    ContinuousCommand()
    : _WasBegan(false)
    , _WasCancelled(false)
    , _WasEnded(false)
    {
    }
    
    ~ContinuousCommand()
    {
        assert(!_WasBegan || (_WasCancelled || _WasEnded));
    }

    // Should be called by the party that began the command to end the command.
    std::function<void (void)> End;
    
    // Should be called by the party that began the command to cancel the command.
    std::function<void (void)> Cancel;
    
    void SetWasBegan()
    {
        assert(!_WasBegan && !_WasCancelled && !_WasEnded);
        _WasBegan = true;
    }
    
    void SetWasEnded()
    {
        assert(_WasBegan && !_WasCancelled && !_WasEnded);
        _WasEnded = true;
    }
    
    void SetWasCancelled()
    {
        assert(_WasBegan && !_WasCancelled && !_WasEnded);
        _WasCancelled = true;
    }
};
