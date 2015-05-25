//
//  ViewModelTest.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/25/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include <iostream>
#include "DinnerViewModel.h"
#include "BreakfastViewModel.h"
#include "CommandDispatcher.h"
#include <boost/mpl/for_each.hpp>

using namespace std;

struct ExtractAndDispatchCommand
{
    template< typename U > void operator()(U x)
    {
        std::cout << "  Discovered command: " << typeid(x).name() << std::endl;
        CommandDispatcher::GlobalDispatcher()->Dispatch(make_shared<U>());
    }
};

void ViewModelTest()
{
    printf("ViewModelTest\n");
    printf("-------------\n");
    
    {
        printf("Test simple command hookup:\n");
        auto breakfast = BreakfastViewModel::New();
        breakfast->Execute(make_shared<SetTableCommand>());
        
        // Output:
        //   Set the table for breakfast
    }
    
    printf("\n");
    
    {
        printf("Test BlockMode:\n");
        auto dinner = DinnerViewModel::New();
        dinner->Execute(make_shared<SetTableCommand>());
        
        {
            auto dineCommand = make_shared<DineCommand>("oxtail");
            assert(dinner->BlockMode() == ViewModelBlockMode::None);
            
            dinner->Begin(dineCommand);
            assert(dinner->BlockMode() == ViewModelBlockMode::Edit);
            
            dineCommand->End();
            assert(dinner->BlockMode() == ViewModelBlockMode::None);
        }
        
        {
            auto dineCommand = make_shared<DineCommand>("cake");
            assert(dinner->BlockMode() == ViewModelBlockMode::None);
            
            dinner->Begin(dineCommand);
            assert(dinner->BlockMode() == ViewModelBlockMode::Edit);
            
            dineCommand->Cancel();
            assert(dinner->BlockMode() == ViewModelBlockMode::None);
        }
        
        // Output:
        //  Set the table for dinner
        //  Beginning dinner
        //  Dinner finished. The oxtail was lovely.
        //  Beginning dinner
        //  Dinner ended early. We'll save the cake for later.
    }
    
    printf("\n");
    
    {
        printf("Test command binding:\n");
        auto dinner = DinnerViewModel::New();
        auto setTable = CommandBinding::New(dinner,
                                            make_shared<SetTableCommand>());
        setTable->Execute();
        
        // Output:
        //   Set the table for dinner
    }
    
    printf("\n");
    
    {
        printf("Test command dispatch:\n");
        auto breakfast = BreakfastViewModel::New();
        CommandDispatcher::GlobalDispatcher()->RegisterReceiver<SetTableCommand>(breakfast);
        
        auto dinner = DinnerViewModel::New();
        CommandDispatcher::GlobalDispatcher()->RegisterReceiver<SetTableCommand>(dinner);
        
        CommandDispatcher::GlobalDispatcher()->Dispatch(make_shared<SetTableCommand>());
        
        // Output:
        //   Set the table for breakfast
        //   Set the table for dinner
    }
    
    
    printf("\n");
    
    {
        printf("Test command discovery:\n");
        auto dinner = DinnerViewModel::New();
        CommandDispatcher::GlobalDispatcher()->RegisterReceiver<SetTableCommand>(dinner);
        boost::mpl::for_each<DinnerViewModel::Commands>(ExtractAndDispatchCommand());
        
        // Output:
        //   Discovered command: 15SetTableCommand
        //   Set the table for dinner
    }
}