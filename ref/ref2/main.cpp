
//#include <stdio.h>
//#include<assert.h>
#include<iostream>


using namespace std;
#define  N 10

int main()
{

    int num = 100;
    cout << num << endl;
    cout << __FILE__ << endl;
    cout << __LINE__ << endl;
    cout << __DATE__ << endl;
    cout << __TIME__ << endl;
    cout << __FUNCTION__ << endl;

    cin.get();

}

#define M
int main1()
{

    char  num = 10;
    //字节>4
#ifdef  M
     //static_assert(sizeof(num) >= 4, "yincheng error");
#endif
    //调试代码，迅速代码错误在哪一行

}
