#include <iostream>
#include <array>

using namespace std;


int main()
{
array<int,5> ar={1,2,3,4,5};
for(auto i=ar.rbegin();i!=ar.rend();++i)
    cout<<*i<<endl;



return 0;
}
