#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    int a[5]={1,2,3,4,5};
    int *p=a;
    cout<<a<<endl;
    for(int i=0;i<5;++i)
    {
        cout<<*p<<endl;
        p++;
    }
    cout<<*(p-1)<<endl;
    char c[10]="abcdefghi";
    char *p1=c;
    char**ptr=&p1;
    cout<<c<<endl;
    for(int i=0;i<10;++i)
    {
//        cout<<*p1<<endl;
//        p1++;
//        cout<<c<<endl;
//        cout<<&p1<<endl;
//        cout<<ptr<<endl;
//        cout<<*ptr<<endl;
//        cout<<**ptr<<endl;
    }

    return 0;
}

