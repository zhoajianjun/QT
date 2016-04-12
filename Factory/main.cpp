#include <iostream>
#include "factory.h"
#include "product.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    Factory* fac=new ConcreateFactory();
    Product* p=fac->CreateProduct();

    delete fac;delete p;
    return 0;
}

