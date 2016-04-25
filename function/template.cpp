#include <iostream>
using namespace std;

template<class T>
T add(T a,T b)
{
    return a+b;
}

int main()
{

cout<<add<int>(1,2)<<endl;
return 0;
}
