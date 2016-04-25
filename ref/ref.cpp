#include <iostream>
#include <functional>
using namespace std;

template<class T>
void com(T arg)
{
cout<<"com="<<&arg<<endl;
arg++;
}
int main()
{
int c1=10;
int& rcount = c1;
com(ref(c1));
cout<<c1<<endl;
return 0;
}
