#include <iostream>
#include <array>
#include <iterator>

using namespace std;

int main()
{
array<int,5> array1={1,2,3,4,5};
array<int,5> array2=array1;
for(auto it=array1.begin();it!=array1.end();++it)
{

cout<<*it<<endl;;
}


return 0;
}
