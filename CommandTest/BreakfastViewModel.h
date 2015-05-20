//
//  BreakfastViewModel.h
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#pragma once

#include "ViewModel.h"

class BreakfastViewModel : public virtual ViewModel
{
public:
    
    template<class T>
    void Execute(const std::shared_ptr<T> &command);
    
    template<class T>
    void Begin(const std::shared_ptr<T> &command);
    
    static std::shared_ptr<BreakfastViewModel> New();
};