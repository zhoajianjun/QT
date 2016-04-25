#include <iostream>
#include <vector>
#include <boost/bind.hpp>
#include <algorithm>


using namespace std;
using namespace boost;
class demo
{

public:
    int add(int a,int b)
    {
        return a+b;
    }
};

int main1()
{
    demo a,&ra=a;
    demo*p=&a;
    cout<<bind(&demo::add,a,_1,11)(10)<<endl;
    cout<<bind(&demo::add,ra,11,12)()<<endl;
    cout<<bind(&demo::add,p,_1,_2)(11,12)<<endl;
    return 0;
}
struct point
{
    int x;
    int y;
    point(int a=0,int b=0):x(a),y(b)
    {

    }
    void print()
    {
        cout<<x<<"=>"<<y<<endl;
    }


};
int main2()
{
    vector<point> v(10);
    std::for_each(v.begin(),v.end(),bind(&point::print,_1));

    return 0;
}
int main()
{
    vector<point> v;
    point a(12,13);
    point b(14,15);
    v.push_back(a);
    v.push_back(b);
    vector<int> v2;
    std::transform(v.begin(),v.end(),v2.begin(),bind(&point::x,_1));
    for(auto &k:v2)
        cout<<k<<",";
//    cout<<bind(&point::x,v[0])()<<endl;

    return 0;
}
int main4()
{
    typedef pair<int ,string> par;
    par p(123,"aaa");
    auto y=bind(&par::first,p)();
    cout<<y<<endl;
    cout<<bind(&par::second,p)()<<endl;

    return 0;
}
int main5()
{
    cout<<bind(greater<int>(),_1,10)(10)<<endl;
    cout<<bind(plus<int>(),_1,_2)(10,11)<<endl;
    cout<<bind(modulus<int>(),_1,3)(10)<<endl;

    return 0;
}

