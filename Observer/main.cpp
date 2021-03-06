#include <iostream>
#include <string>
#include <list>
using namespace std;

//观察者模式：观察者模式定义了一种一队多的依赖关系，
//让多个观察者对象同时监听某一个主题对象。
//这个主题对象在状态上发生变化时，会通知所有观察者对象，
//使他们能够自动更新自己。
//
//想知道咱们公司最新MM情报吗？加入公司的MM情报邮件组就行了，
//tom负责搜集情报，他发现的新情报不用一个一个通知我们，
//直接发布给邮件组，我们作为订阅者（观察者）就可以及时收到情报啦。

// 监视，观察者，都有一个基类，派生，实现不同的效果
//监视者的类，管理所有的观察者，增加或者删除，发出消息，让观察者处理
//观察者的类需要接受消息并处理


class Subject; //可以使用subject

class Observer
{
protected:
	string name;
	Subject *sub;
public:
	Observer(string name, Subject *sub)//观察者的名字， 监视与通知的类
	{
		this->name = name;//输入名字
		this->sub = sub;//设置谁来通知我
	}
	virtual void update() = 0;//纯虚函数
};

class StockObserver :public Observer //继承，自己实现刷新函数
{
public:
	StockObserver(string name, Subject *sub) :Observer(name, sub)
	{
	}
	void update();
};
void StockObserver::update()
{
	cout << name << " 收到消息：" << sub->action << endl;
	if (sub->action == "梁所长来了!")
	{
		cout << "我马上关闭股票，装做很认真工作的样子！" << endl;
	}
	if (sub->action == "去喝酒！")
	{
		cout << "我马上走" << endl;
	}
}

class NBAObserver :public Observer
{
public:
	NBAObserver(string name, Subject *sub) :Observer(name, sub)
	{
	}
	void update();
};

void NBAObserver::update()
{
	cout << name << " 收到消息：" << sub->action << endl;
	if (sub->action == "梁所长来了!")
	{
		cout << "我马上关闭NBA，装做很认真工作的样子！" << endl;
	}

   if (sub->action == "去喝酒！")
   {
    cout << "我马上拍" << endl;
    }
}


class Subject  //
{
protected:
	list<Observer*> observers;///存储观察者的指针，链表
public:
	string action;
	virtual void attach(Observer*) = 0;
	virtual void detach(Observer*) = 0;
	virtual void notify() = 0;//实现监听的基类
};




class Secretary :public Subject
{
	void attach(Observer *observer)  //载入通知的列表
	{
		observers.push_back(observer);
	}
	void detach(Observer *observer)//删除
	{
		list<Observer *>::iterator iter = observers.begin();
		while (iter != observers.end())
		{
			if ((*iter) == observer)
			{
				observers.erase(iter);
			}
			++iter;
		}
	}
	void notify()  ///通知函数
	{
		list<Observer *>::iterator iter = observers.begin();
		while (iter != observers.end())
		{
			(*iter)->update();
			++iter;
		}
	}
};



void NBAObserver::update()
{
	cout << name << " 收到消息：" << sub->action << endl;
	if (sub->action == "梁所长来了!")
	{
		cout << "我马上关闭NBA，装做很认真工作的样子！" << endl;
	}

   if (sub->action == "去喝酒！")
   {
    cout << "我马上拍" << endl;
    }
}

int main()
{
	Subject *dwq = new Secretary();//消息监视，监视

	Observer *xs = new NBAObserver("xiaoshuai", dwq);//订阅消息
	Observer *zy = new NBAObserver("zouyue", dwq);
	Observer *lm = new StockObserver("limin", dwq);

	dwq->attach(xs);
	dwq->attach(zy);
	dwq->attach(lm);//增加到队列

	dwq->action = "去吃饭了！";
	dwq->notify();
//	dwq->action = "去喝酒！";
//	dwq->notify();
//	cout << endl;
//	dwq->action = "梁所长来了!";
//	dwq->notify();
	cin.get();
	return 0;
}
