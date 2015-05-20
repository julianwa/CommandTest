//
//  ViewModel.h
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#include <memory>
#include <string>

enum ViewModelBlockMode
{
    None = 0,
    Navigate,
    Edit
};

class ViewModel
{
public:
    
    virtual ViewModelBlockMode BlockMode() = 0;
    
    virtual std::string Name() = 0;
};
