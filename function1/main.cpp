#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost;

int f(int a,int b)
{
    return a+b;
}

int main1()
{
    cout << "Hello World!" << endl;
    function<int(int,int)> func;
    func=f;
    cout<<func(10,20)<<endl;
    return 0;
}
struct demo
{

    int add(int a,int b)
    {
        return a+b;
    }
    int operator ()(int x)const
    {
        return x*x;
    }
};

int main()
{
    function<int(demo&,int,int)> func1;
    function<int(int,int)>func2;
    func1=bind(&demo::add,_1,_2,_3);
    demo sr;
    func2=bind(&demo::add,sr,_1,_2);

    cout<<func2(10,12);
    cout<<func1(sr,10,12);

    return 0;
}
class demo_class

{
private:

    typedef function<void(int)> func_t;
    func_t func;
    int n;
public:
    demo_class(int i):n(i){}
    template<class CallBack>
    void accept(CallBack f)
    {
        func=f;
    }
    void run(int b)
    {
        if(b>5)
        {
            func(n);
        }
        else
        {
            return;
        }
    }
};
void call_back_func(int i)
{
    cout<<"call back func";
    cout<<i*2<<endl;
}
void call_back_func1(int i)
{
    cout<<"call back func1";
    cout<<i*5<<endl;
}

int main3()
{
    demo_class dem(10);
    dem.accept(call_back_func1);
    dem.run(6);


    return 0;
}
