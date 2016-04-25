#include <iostream>
class A
{
public:

    A()
    {
        num=10;
    }
    ~A()
    {

    }
public:
    int num;
};

using namespace std;

int main()
{
    const A *ca=new A;
    A*cb=const_cast<A*>(ca);
    cb->num=20;
    cout<<cb->num<<"****"<<ca->num<<endl;

    const int ica = 100;
    int * ia = const_cast<int *>(&ica);
    *ia = 200;
    cout<< *ia <<ica<<endl;

    cout << "Hello World!" << endl;
    return 0;
}

