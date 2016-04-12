#ifndef COREFACTORY_H
#define COREFACTORY_H
class SingleCore;
class MultiCore;

class CoreFactory
{
public:
    CoreFactory();
    virtual SingleCore* CreateSingleCore() = 0;
    virtual MultiCore* CreateMultiCore() = 0;
};

#endif // COREFACTORY_H
