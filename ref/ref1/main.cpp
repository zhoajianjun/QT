#include<iostream>
//#include <algorithm>
#include <functional>
using namespace std;

template<class T>
void com(T arg)//模板函数，引用无效，引用包装器
{
    std::cout <<"com ="<< &arg << "\n";
    arg++;
}


int main()
{
    int count = 10;
    int  & rcount = count;
    com(count);
    std::cout << count << std::endl;
    //std::ref(变量) ，函数模板,引用包装器
    com(ref(count));
    com(rcount);
    std::cout << "main=" << &rcount << "\n";
    std::cout << count << std::endl;
    std::cin.get();

}
