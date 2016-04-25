#include <iostream>
#include <array>
#include <vector>
#include <iterator>

using namespace std;

int main1()
{
    cout << "Hello World!" << endl;
    array<int,4> array1={1,2,3,4};
    for(int i=0;i<4;++i)
    {
        cout<<array1[i]<<endl;
    }
    return 0;
}
int main()
{
    vector<int> myvector={1,1,1,11,2,1,1};
    vector<int> ::iterator inter1,inter2;
    inter1=myvector.begin();
    inter2=myvector.end();
    while(inter1!=inter2)
    {
        cout<<*inter1<<endl;
        ++inter1;
    }
//	vector <string>  string1;//动态字符串数组
//	string1.push_back("notepad");
//	string1.push_back("calc");
//	string1.push_back("mspaint");

//	vector<string>::iterator ibegin, iend;//迭代器
//	ibegin = string1.begin();//数据起始点
//	iend = string1.end();//结束

//	for (;ibegin!=iend;ibegin++)
//	{
//		string tempstr = *ibegin;//获取指针指向的数据;//执行指令
//		cout<<*ibegin<<endl;
//	}

    return 0;
}

