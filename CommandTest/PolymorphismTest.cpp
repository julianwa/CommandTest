//
//  PolymorphismTest.cpp
//  CommandTest
//
//  Created by Julian Walker on 5/25/15.
//  Copyright (c) 2015 Julian Walker. All rights reserved.
//

#include "CommandReceiver.h"
#include "CommandReceiverImpl.hpp"

using namespace std;

#pragma mark - Commands

class TestCommand : public Command {};
class OnlyDerivedTestCommand : public Command {};

#pragma mark - BaseClass

class BaseClass
: public virtual CommandReceiver<BaseClass>
{
public:
    
    using Commands = boost::mpl::set<TestCommand>;
    using ContinuousCommands = boost::mpl::set<>;
};

class BaseClassImpl
: public virtual BaseClass
, public virtual CommandReceiverImpl
{
public:
    virtual void HandleExecute(const shared_ptr<TestCommand> &command)
    {
        printf("  BaseClassImpl did execute TestCommand\n");
    }
};

COMMAND_RECEIVER_IMPL(BaseClass)

#pragma mark - DerivedClass

class DerivedClass
: public virtual CommandReceiver<DerivedClass>
, public virtual BaseClass
{
public:
    using Commands = boost::mpl::set<TestCommand, OnlyDerivedTestCommand>;
    using ContinuousCommands = boost::mpl::set<>;
};

class DerivedClassImpl
: public virtual DerivedClass
, public virtual BaseClassImpl
{
public:
    virtual void HandleExecute(const shared_ptr<TestCommand> &command)
    {
        BaseClassImpl::HandleExecute(command);
        printf("  DerivedClassImpl did execute TestCommand\n");
    }
    
    void HandleExecute(const shared_ptr<OnlyDerivedTestCommand> &command)
    {
        printf("  DerivedClassImpl did execute OnlyDerivedTestCommand\n");
    }
};

COMMAND_RECEIVER_IMPL(DerivedClass);

#pragma mark -

void PolymorphismTest()
{
    printf("PolymorphismTest\n\n");

    printf("Executing command against derived class:\n");
    shared_ptr<DerivedClass> derivedClass = make_shared<DerivedClassImpl>();
    derivedClass->CommandReceiver<DerivedClass>::Execute(make_shared<TestCommand>());
    
    printf("\n");
    
    printf("Executing command against base class:\n");
    shared_ptr<BaseClass> baseClass = static_pointer_cast<BaseClass>(derivedClass);
    baseClass->Execute(make_shared<TestCommand>());
    
    printf ("\n");
    
    printf("Execting derived-only command against dervied class:\n");
    derivedClass->CommandReceiver<DerivedClass>::Execute(make_shared<OnlyDerivedTestCommand>());
}