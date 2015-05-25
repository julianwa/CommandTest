//
//  main.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/13/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include <iostream>

using namespace std;

extern void ViewModelTest();
extern void PolymorphismTest();

int main(int argc, const char * argv[])
{
    ViewModelTest();
    
    printf("\n\n");
    
    PolymorphismTest();
    
    return 0;
}
