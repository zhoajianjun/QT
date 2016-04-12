#ifndef PRODUCT_H
#define PRODUCT_H


class Product
{
public:
    Product();
    virtual ~Product()=0;
};
class ConcreteProduct:public Product
{
public:
    ConcreteProduct();
    ~ConcreteProduct();
};

#endif // PRODUCT_H
