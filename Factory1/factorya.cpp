#include "singlecore.h"
#include "multicore.h"
#include "corefactory.h"
#include "singlecorea.h"
#include "multicorea.h"
#include "factorya.h"

FactoryA::FactoryA()
{

}

SingleCore *FactoryA::CreateSingleCore()
{
    return new SingleCoreA();
}

MultiCore *FactoryA::CreateMultiCore()
{
    return new MultiCoreA();
}

