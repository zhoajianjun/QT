#include <iostream>

using namespace std;
//没有名字的命名空间中的变量和函数可以直接调用
namespace {
int a=10;
void print()
{
    cout<<"kkkk"<<endl;
}
}
namespace run {
int (*P)(int,int);//函数指针
int (*&rp(int(*&p1)(int,int)))(int,int);//函数指针的引用

}
int jia(int a,int b)
{
    return a+b;
}
int jian(int a,int b)
{
    return a-b;
}
int (*&rp(int(*&p1)(int,int ),int b))(int,int)
{
    cout<<b<<endl;
    p1=jia;
    return p1;

}

int main()
{
    cout << "Hello World!" << endl;
    cout<<a<<endl;
    print();
    run::P=jian;
    cout<<run::P(1,20)<<endl;
    run::P=rp(run::P,5);
    cout<<run::P(1,2)<<endl;
    return 0;
}

