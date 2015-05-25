//
//  main.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include <iostream>
#include "DinnerViewModel.h"
#include "BreakfastViewModel.h"
#include "CommandDispatcher.h"
#include <boost/mpl/for_each.hpp>

using namespace std;

extern void PolymorphismTest();

struct ExtractCommand
{
    template< typename U > void operator()(U x)
    {
        std::cout << "Discovered command: " << typeid(x).name() << std::endl;
        CommandDispatcher::GlobalDispatcher()->Dispatch(make_shared<U>());
    }
};

int main(int argc, const char * argv[]) {

    {
        auto breakfast = BreakfastViewModel::New();
        breakfast->Execute(make_shared<SetTableCommand>());
    }
    
    printf("-------------\n");
    
    {
        auto dinner = DinnerViewModel::New();
        dinner->Execute(make_shared<SetTableCommand>());

        auto dineCommand = make_shared<DineCommand>("oxtail");
        assert(dinner->BlockMode() == ViewModelBlockMode::None);
        
        dinner->Begin(dineCommand);
        assert(dinner->BlockMode() == ViewModelBlockMode::Edit);
        
        dineCommand->End();
        assert(dinner->BlockMode() == ViewModelBlockMode::None);
    }
    
    printf("-------------\n");
    
    {
        auto dinner = DinnerViewModel::New();
        auto setTable = CommandBinding::New(dinner,
                                            make_shared<SetTableCommand>());
        setTable->Execute();
    }
    
    printf("-------------\n");
    
    {
        auto breakfast = BreakfastViewModel::New();
        CommandDispatcher::GlobalDispatcher()->RegisterReceiver<SetTableCommand>(breakfast);
        
        auto dinner = DinnerViewModel::New();
        CommandDispatcher::GlobalDispatcher()->RegisterReceiver<SetTableCommand>(dinner);
        
        CommandDispatcher::GlobalDispatcher()->Dispatch(make_shared<SetTableCommand>());
        
        boost::mpl::for_each<DinnerViewModel::Commands>(ExtractCommand());
    }
    
    printf("-------------\n");
    PolymorphismTest();
    
    return 0;
}
