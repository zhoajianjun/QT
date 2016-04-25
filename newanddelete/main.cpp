#include <iostream>
#include<malloc.h>

using namespace std;
class A
{
public:
    A()
    {
        cout<<"create"<<endl;
    }
    ~A()
    {
        cout<<"destroy"<<endl;
    }
    void* operator new(size_t size)
    {
        cout<<"A"<<endl;
        void*p=malloc(size);
        return p;
    }
    void* operator new[](size_t size)
    {
        return operator new(size);
    }

    void operator delete(void*p)
    {
        free(p);
        cout<<"~A"<<endl;
    }
    void operator delete[](void*p)
    {

        return operator delete(p);
    }

private:

};

int main()
{
    A *a=new A[3];
    delete [] a;
    cout << "Hello World!" << endl;
    return 0;
}
/*#include<iostream>
#include<stdlib.h>
//全局的new  delete监视所有释放分配
//局部的new delete监视某个类的所有分配释放
//

void *operator new(size_t size)
{

	if (size == 0)
	{
		return 0;
	}
	void *p = malloc(size);
	std::cout << "全局被调用内存被分配"<<p<<std::endl;
	return p;
}

void  operator delete (void *p)
{
	std::cout << "全局被调用内存被释放" << p << std::endl;
	free(p);

}
void *operator new[](size_t size)
{
	return operator new(size);//每个对象挨个调用已经重载好的new，调用构造

}

void operator delete[](void*p)
{
	return operator delete(p);//每个对象挨个调用已经重载好的delete,调用析构
}


class tansheng
{
public:
	static int jishuqi;//静态
	int *p;
	int length;
public:
	tansheng()//构建的时候初始化
	{
		//this->length = 10;
		std::cout << "11谭胜被创建" << std::endl;
	}
	~tansheng()//删除的时候释放内存
	{
		std::cout << "11谭胜被销毁" << std::endl;
	}

	static void * operator new(size_t size)
	{
		jishuqi += 1;
		std::cout << "a对象被创建" << std::endl;
		tansheng *ptemp = ::new tansheng;//劫持
		return ptemp;

	}
	static void * operator new[](size_t size)
	{

		std::cout << "a1对象数组被创建" << std::endl;
		return  operator  new(size);

	}


	static void  operator delete(void *p)
	{
		jishuqi -= 1;
		std::cout << "b2对象被销毁" << std::endl;
		::delete p;//::全局
	}
	static void  operator delete[](void *p)
	{
		std::cout << "a2对象数组被销毁" << std::endl;
		return  operator  delete(p);
	}



};
int tansheng::jishuqi = 0;

int main1()
{
	//int *p = new int[10];
	//delete[]p;

	tansheng *p1 = new tansheng[5];
	delete  []p1;

}






int main()
{
	int  *p = new int(8);

	delete p;

}

//int *p=new int[10]
//delete []p;*/

