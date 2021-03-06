#include <string>
#include <iostream>
using namespace std;

//装饰模式：装饰模式以对客户端透明的方式扩展对象的功能，
//是继承关系的一个替代方案，提供比继承更多的灵活性。
//动态给一个对象增加功能，这些功能可以再动态的撤消。
//增加由一些基本功能的排列组合而产生的非常大量的功能。
//
//Mary过完轮到Sarly过生日，还是不要叫她自己挑了，
//不然这个月伙食费肯定玩完，拿出我去年在华山顶上照的照片，
//在背面写上“最好的的礼物，就是爱你的Fita”，
//再到街上礼品店买了个像框（卖礼品的MM也很漂亮哦），
//再找隔壁搞美术设计的Mike设计了一个漂亮的盒子装起来……，
//我们都是Decorator，最终都在修饰我这个人呀，怎么样，看懂了吗？




class Person
{
private:
	string m_strName;
public:
	Person(string strName)
	{
		m_strName = strName;
	}
	Person(){}
	virtual void show()
	{
		cout << "装扮的是:" << m_strName << endl;
	}
};

class Finery :public Person
{
protected:
	Person *m_component;
public:
	void decorate(Person* component)
	{
		m_component = component;
	}
	virtual void show()
	{
		m_component->show();
	}
};

class TShirts :public Finery
{
public:
	virtual void show()
	{
		m_component->show();
		cout << "T shirts" << endl;
	}
};

class BigTrouser :public Finery
{
public:
	virtual void show()
	{
		m_component->show();
		cout << "Big Trouser" << endl;
	}
};

int main()
{
	Person *p = new Person("小李");
	BigTrouser *bt = new BigTrouser();
	TShirts *ts = new TShirts();

	bt->decorate(p);
	ts->decorate(bt);
	ts->show();
	cin.get();
	return 0;
}
