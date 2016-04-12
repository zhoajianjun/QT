#ifndef FACTORY_H
#define FACTORY_H
class Product;

class Factory
{
public:
    Factory();
    virtual ~Factory()=0;
    virtual Product* CreateProduct()=0;
};
class ConcreateFactory : public Factory
{
public:
    ConcreateFactory();
    ~ConcreateFactory();
    Product* CreateProduct();
};

#endif // FACTORY_H
