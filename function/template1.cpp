#include <iostream>

using namespace std;

struct info
{
char name[40];
double db;
int data;
};
template<typename T>
void swap(T &a, T &b)
{
std::cout << "通用函数模板" << std::endl;
T temp = a;
a = b;
b = temp;//交换两个变量

}
/*void swap(info &info1, info &info2)
{
std::cout << "特有函数模板" << std::endl;
//通用模板可以实现通用，针对自己的数据类型做出优化
info temp = info1;
info1 = info2;
info2 = temp;
}*/
int main()
{
info info1={"aaa",20.2,10};
info info2={"bbb",9.2,1};
//swap(info1,info2);
cout<<info1.name<<info1.db<<info1.data<<endl;
int ch1=1;
int ch2=2;
swap<int>(ch1,ch2);
cout<<ch1<<ch2<<endl;




}
