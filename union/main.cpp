#include <iostream>

#include <string>

#include <iomanip>  //因为在输出流中使用了控制符setw

using namespace std;

struct                //声明匿名的结构体
{

    int num;

    char name[10];

    char sex;

    char job;

    union P              //声明共用体类型

    {

        int grade;       //年级

        char position[10]; //职务

    }category;       //成员category为共用体变量

}person[2];         //定义共用体数组person，含两个元素（个人认为就是结构体类型变量）


int main()

{

    int i ;

    for(i=0;i<2;i++)

    {

        cin>>person[i].num>>person[i].name>>person[i].sex>>person[i].job;

        if(person[i].job=='s')

        {

            cin>>person[i].category.position;

        }else if(person[i].job=='t')

        {

            cin>>person[i].category.position;

        }

        cout<<endl<<"No.Name sex job grade/position"<<endl;

    }

    for(i=0;i<2;i++)

    {

        if(person[i].job=='s')

        {

            cout<<person[i].num<<setw(6)<<person[i].name<<""<<person[i].sex<<""<<person[i].job<<setw(10)<<person[i].category.grade<<endl;

        }else{

            cout<<person[i].num<<setw(6)<<person[i].name<<""<<person[i].sex<<" "<<person[i].job<<setw(10)<<person[i].category.position<<endl;

        }

    }

    return 0;

}

