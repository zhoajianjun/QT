#include <iostream>
#include <array>

using namespace std;

int main()
{
array<int,5> array1;
for(int i=0;i<5;++i)
{
array1.at(i)=i+1;
}
for(int i=0;i<5;++i)
cout<<array1.at(i)<<endl;

return 0;
}
