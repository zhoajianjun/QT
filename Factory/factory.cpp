#include "factory.h"
#include "product.h"
#include <iostream>
using namespace std;

Factory::Factory()
{

}

Factory::~Factory()
{

}

ConcreateFactory::ConcreateFactory()
{
    cout<<"factory"<<endl;
}

ConcreateFactory::~ConcreateFactory()
{
    cout<<"~factory"<<endl;
}

Product *ConcreateFactory::CreateProduct()
{
    return new ConcreteProduct();
}
