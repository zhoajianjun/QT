#include<iostream>
#include<stdlib.h>
//	int a[10]
//  int (&ra)[10]
//   int a[2][5]
//   int (&ra)[2][5]
void main1()
{
        int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        int(&ra)[10](a);//引用就是给原来的变量有一个别名同一个地址
        int  i = 0;
        for (auto data: ra)//C++11的循环
        {
                data = i + 5;
                std::cout << data << std::endl;
        }
        std::cout << a << ra << std::endl;
        std::cout << &a << &ra << std::endl;
        system("pause");
}

void main2()
{
        int a[2][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        int(&ra)[2][5](a);//引用就是给原来的变量有一个别名同一个地址
        for (int i = 0; i < 2; i++)
        {
                for (int j = 0; j < 5; j++)
                {
                        std::cout << " " << ra[i][j];
                }
                std::cout << "\n";
        }
        std::cout << a << ra << std::endl;
        std::cout << &a << &ra << std::endl;
        system("pause");
}

int jia(int a, int b)
{
        return a + b;
}
int jian(int a, int b)
{
        return a - b;
}

void change(int(* & rp)(int,int))
{
        rp = jian;
}

void main3()
{
        int(* p)(int a, int b)(jia);
        std::cout << p(1, 2) << std::endl;
        //int(*&rp)(int a, int b)(p);//引用函数指针
        //rp=jian;//（）仅仅适用于初始化
        change(p);
        std::cout << p(1, 2) << std::endl;
        system("pause");
}

int(*& changep(int (*&rp)(int,int)))(int, int)
{
        rp = jian;
        return rp;
}
int main()
{
        int(*p)(int a, int b)(jia);
        std::cout << p(1, 2) << std::endl;
        //p = changep(p);
        change(p);
        std::cout << p(1, 2) << std::endl;
}

void main5()
{
        //int *p[4];
        int a = 1, b = 2, c = 3;
        int *px[3] = { &a, &b, &c };
        //int && p [4] = {a,b,c };
        //引用数组是非法的
}
struct mystr
{
        int b;
        double a;
        char c;
        char d;
        //代码区的函数不计入结构体的sizeof
        void go()
        {
                std::cout << "123456789" << std::endl;
        }
};
class MyClass
{
        char a;
        char b;
        char c;//引用的本质是指针，直接sizeof引用，就是求引用的数据大小
        //引用变量占据4个字节
        double d;

};

int main6()
{
        int num = 10;
        int & rnum(num);
        double db = 10.9;
        double & rdb(db);//直接作用引用的变量

        std::cout << sizeof(rnum) << std::endl;
        std::cout << sizeof(mystr) <<std::endl;
        std::cout << sizeof(rdb) << std::endl;
        std::cout << sizeof(MyClass) << std::endl;
}

int  getdata(int && num)//右值引用，节约内存拷贝，内存优化所必须
{
        std::cout << num << std::endl;
        num += 10;
        return num;
}


void  main7()
{
        int a = 5;
        int b = 4;

        std::cout << getdata(a+1) << std::endl;

}
//左值，一般可以取地址就是左值
//右值某些情况可以，某些情况不可以
void main8()
{
        int a = 3;
        int b = a + 1;//右值->左值
        std::cout << getdata(std::move(a) ) << std::endl;
        //std::move将左值转换为右值，C++11

}
void main9()
{
        //const int num(6);
        char str[10]="hello";//限定字符串不被修改
        const char *pc(str);//指向常量的指针限定了指向的数据无法修改,+1，+2，+3
        str[3] = 'x';//可以，
        //pc[3] = 'y';
        //*(pc + 3) = 'y';
        pc = "world";

}

void main10()
{
        char str[10]="hello";
        const char(&rstr)[10](str);//常量引用
        const char(&rrstr)[10](rstr);//引用可以给另一个引用初始化
        str[4] = 'X';
        //rstr[4] = 'Y';

}

void  main11()
{
        int(*p)(int a, int b)(jia);
        std::cout << p(1, 2) << std::endl;
        int(* const &rp)(int a, int b)(p);//引用函数指针
        //rp=jian;//（）仅仅适用于初始化

}
