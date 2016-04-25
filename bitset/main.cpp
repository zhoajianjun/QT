#include <set>
#include <bitset>
#include <iostream>
#include<string>

using namespace std;



int main1()
{

		  //8 位， （215）代表构造的数据
	bitset<8>bs(215);
	for (int i = 0; i < 8;i++)//最高位存储i=7上
	{
		cout << bs[i];
	}

	cin.get();









	cin.get();
}


int main2()
{

	//8 位， （215）代表构造的数据
	bitset<8>bs(215);
	for (int i = 7; i >=0; i--)
	{
		cout << bs[i] << "  " << ~bs[i] << endl;

	}

	cin.get();









	cin.get();
}

int  main()
{
	float num = 1231231236.8;
	bitset<32> myset(num);
	for (int i = 31; i >=0;i--)
	{
		cout << myset[i];
	}




	cin.get();





}

void  main3S()
{
	int  num =-5;
	bitset<32> myset(num);
	for (int i = 31; i >= 0; i--)
	{
		cout << myset[i];
	}
	string str = myset.to_string();
	cout <<"\n" <<str << endl;

	unsigned int data;
	data = myset.to_ulong();//补码
	cout << "\n" << data<< endl;

	cin.get();





}

void main345()
{
	bitset<8>bs(255);
	bs.set(7, 0);//操作二进制位
	bs.set(0, 0);
	cout << bs.size() << endl;//位数
	//bs.reset();//全部清零
	//bs.none();//测试下是否有越位
	for (int i = 7; i >=0; i--)//最高位存储i=7上
	{
		cout << bs[i];
	}

	cin.get();
}
