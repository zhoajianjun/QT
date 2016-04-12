#include <iostream>
#include "corefactory.h"
#include "factorya.h"
#include "factoryb.h"
#include "singlecore.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    CoreFactory* p=new FactoryA();
    SingleCore* m=p->CreateSingleCore();
    m->Show();
    CoreFactory* p1=new FactoryB();
    SingleCore* m1=p1->CreateSingleCore();
    m1->Show();

    return 0;
}

