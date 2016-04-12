#include <iostream>
#include "resumea.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Resume *r1=new ResumeA("A");
    Resume *r2=new ResumeA("B");
    Resume *r3=r1->Clone();
    Resume *r4=r2->Clone();
    r1->Show();r2->Show();
    delete r1;delete r2;
    r1=r2=NULL;
    r3->Show();r4->Show();
    delete r3;delete r4;
    r3=r4=NULL;
    return 0;
}

