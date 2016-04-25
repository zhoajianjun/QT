#include <iostream>
#include <list>

using namespace std;
#if 0
int main()
{
    list<pair<int,char>> mylist;
//    mylist.emplace(mylist.begin(),100,'x');
//    mylist.emplace(mylist.begin(),200,'y');
//    for(auto&x:mylist)
//        cout<<x.first<<","<<x.second<<endl;
    mylist.emplace_back(10,'a');
    mylist.emplace_back(20,'b');
    mylist.emplace_back(30,'c');
    mylist.emplace_front(40,'d');
    for(auto&x:mylist)
        cout<<"("<<x.first<<","<<x.second<<")"<<endl;
    cout << "Hello World!" << endl;
    return 0;
}
#endif
bool single_digit(const int& value)
{
    return (value<10);
}
struct is_ODD{
    bool operator ()(const int &value)
    {
        return (value%2)==1;
    }
};

int main()
{
int myint[]={10,11,12,13,4,5,14};
list<int> mylist(myint,myint+7);
mylist.remove_if(single_digit);
mylist.remove_if(is_ODD());
for(auto i=mylist.begin();i!=mylist.end();++i)
    cout<<*i<<endl;
    return 0;
}

