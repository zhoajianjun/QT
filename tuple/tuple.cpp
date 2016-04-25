#include <iostream>
#include <tuple>

using namespace std;

int main()
{
tuple<int,char> a(10,'x');
cout<<get<0>(a)<<get<1>(a)<<endl;
tuple<long,char> b;
b=make_tuple(110,'d');
cout<<get<0>(b)<<get<1>(b)<<endl;

    return 0;

}
