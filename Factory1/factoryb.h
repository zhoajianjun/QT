#ifndef FACTORYB_H
#define FACTORYB_H

class CoreFactory;
class SingleCore;
class MultiCore;

class FactoryB : public CoreFactory
{
public:
    FactoryB();
    SingleCore* CreateSingleCore() ;
    MultiCore* CreateMultiCore() ;
};

#endif // FACTORYB_H
