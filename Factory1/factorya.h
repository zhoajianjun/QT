#ifndef FACTORYA_H
#define FACTORYA_H

class CoreFactory;
class SingleCore;
class MultiCore;

class FactoryA : public CoreFactory
{
public:
    FactoryA();
    SingleCore* CreateSingleCore();
    MultiCore* CreateMultiCore();
};

#endif // FACTORYA_H
