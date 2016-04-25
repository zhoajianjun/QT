#include <iostream>
#include <array>

using namespace std;

int main()
{

array<int,5> myarray;
myarray.fill(5);
for(int&x:myarray)
    cout<<x<<endl;


return 0;
}
