#include <iostream>
#include <typeinfo>

using namespace std;

int main1()
{
    auto num=11.1;
    //cout<<typeid(num)<<endl;
    double a[2][5]={1,2,3,4,5,6,7,8,9,0};
    for(auto data:a)
    {
        for(int i=0;i<5;++i)
        {
            cout<<*(data+i)<<endl;
        }
    }
    return 0;
}
int main()
{
    auto a=10;
    auto b=10.1;
    auto *p=&a;
    cout<<typeid(a).name()<<endl;
    cout<<typeid(b).name()<<endl;
    cout<<typeid(p).name()<<endl;
    decltype(a) d(5);
    decltype(b) e(11.1);
    cout<<d<<endl;
    cout<<e<<endl;
    cout<<typeid(e).name()<<endl;


}

