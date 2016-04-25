#include <iostream>
#include <vector>
using namespace std;

int main()
{
vector<int> myvector;
int myint;
do{
cin>>myint;
myvector.push_back(myint);

}while(myint);
for(auto it=myvector.begin();it!=myvector.end();++it)
cout<<*it<<endl;

cout<<myvector.size()<<endl;
return 0;
}

