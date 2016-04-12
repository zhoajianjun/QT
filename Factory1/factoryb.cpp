#include "corefactory.h"
#include "singlecore.h"
#include "multicore.h"
#include "singlecoreb.h"
#include "multicoreb.h"
#include "factoryb.h"

FactoryB::FactoryB()
{

}

SingleCore *FactoryB::CreateSingleCore()
{
    return new SingleCoreB();
}

MultiCore *FactoryB::CreateMultiCore()
{
    return new MultiCoreB();
}

