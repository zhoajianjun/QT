#include "singlecore.h"
#include "singlecoreb.h"
#include <iostream>
using namespace std;

SingleCoreB::SingleCoreB()
{
    cout<<"singlecoreb"<<endl;
}

SingleCoreB::~SingleCoreB()
{
    cout<<"~singlecoreb"<<endl;
}

void SingleCoreB::Show()
{
    cout<<"show b"<<endl;
}

