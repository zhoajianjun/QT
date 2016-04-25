#include <iostream>

using namespace std;
enum color:char{red='A',yellow,white,blue};

int main()
{
    color a=color::red;
    cout<<a<<endl;
    color mycolor = red;
    //mycolor = 'A';//确保在枚举的范围的之内不出错
    mycolor = color::white;//新语法

	color mycolor1(red);
	color mycolor2(color::red);
	cout<<mycolor1<<mycolor2<<endl;
}

