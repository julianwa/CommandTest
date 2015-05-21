//
//  main.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include <iostream>
#include <memory>
#include "DinnerViewModel.h"
#include "BreakfastViewModel.h"
#include "MealCommands.h"
#include "CommandDispatcher.h"
#include <boost/mpl/for_each.hpp>

using namespace std;

struct ExtractCommand
{
    template< typename U > void operator()(U x)
    {
        std::cout << "Discovered command: " << typeid(x).name() << std::endl;
        CommandDispatcher::Instance()->Dispatch(make_shared<U>());
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
        //dineCommand->Cancel();
        assert(dinner->BlockMode() == ViewModelBlockMode::None);
    }
    
    printf("-------------\n");
    
    {
        auto breakfast = BreakfastViewModel::New();
        CommandDispatcher::Instance()->RegisterReceiver<SetTableCommand>(breakfast);
        
        auto dinner = DinnerViewModel::New();
        CommandDispatcher::Instance()->RegisterReceiver<SetTableCommand>(dinner);
        
        CommandDispatcher::Instance()->Dispatch(make_shared<SetTableCommand>());
        
        boost::mpl::for_each<DinnerViewModel::Commands>(ExtractCommand());
    }
    
    return 0;
}
