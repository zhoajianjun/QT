#include <iostream>
#include <string>
using namespace std;
//桥梁模式：将抽象化与实现化脱耦，使得二者可以独立的变化，

//也就是说将他们之间的强关联变成弱关联，

//也就是指在一个软件系统的抽象化和实现化之间使用组合

/// 聚合关系而不是继承关系，从而使两者可以独立的变化。


//
//早上碰到MM，要说早上好，晚上碰到MM，要说晚上好；
//碰到MM穿了件新衣服，要说你的衣服好漂亮哦，碰到MM新做的发型，
//要说你的头发好漂亮哦。不要问我“早上碰到MM新做了个发型怎么说”
//这种问题，自己用BRIDGE组合一下不就行了。

class HandsetSoft
{
public:
	virtual void run() = 0;
};

class HandsetGame :public HandsetSoft
{
public:
	void run()
	{
		cout << "运行手机游戏" << endl;
	}
};

class HandsetAddressList :public HandsetSoft
{
public:
	void run()
	{
		cout << "运行手机通讯录" << endl;
	}
};
class HandsetQQ:public HandsetSoft
{
public:
	void run()
	{
		cout<<"运行QQ"<<endl;
	}
};

class HandsetBrand
{
protected:
	HandsetSoft *soft;
public:
	void setHandsetSoft(HandsetSoft *soft)
	{
		this->soft = soft;
	}
	virtual void run() = 0;
};
/*
class HandsetBrandN :public HandsetBrand
{
public:
	void run()
	{
		soft->run();
	}
};
*/

class HandsetBrandM :public HandsetBrand
{
public:
	void run()
	{
		soft->run();
	}
};
void runs(HandsetBrand*p)
{
	p->run();
}
void (*ptr)(HandsetBrand*p);

int main()
{
	HandsetBrand *hb = new HandsetBrandM();

	hb->setHandsetSoft(new HandsetGame());
	hb->run();
	hb->setHandsetSoft(new HandsetAddressList());
	hb->run();

	hb->setHandsetSoft(new HandsetQQ());
	hb->run();
	ptr=runs;
	ptr(hb);


	cin.get();
	return 0;
}
