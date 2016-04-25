#include <iostream>
#include <tuple>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    int a=10;
    char b='a';
    string c="aaa";
    tuple<int,char,string>mytuple(a,b,c);
    auto data=get<0>(mytuple);
    auto data1=get<1>(mytuple);
    auto data2=get<2>(mytuple);
    cout<<data<<endl<<data1<<endl<<data2<<endl;
    return 0;
}

