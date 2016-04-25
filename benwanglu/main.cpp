
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Memo
{
public:

	Memo(string state)
	{
		this->state=state;
	}
	string getState() const
	{
		return state;
	}

private:
	string state;
};

class Originator
{
public:

	void setMemo(Memo *memo)
	{
		state=memo->getState();
	}
	Memo *createMemo()
	{
		return new Memo(state);
	}
	void show()
	{
		cout<<state<<endl;
	}
	void setState(const string &value)
	{
		state = value;
	}

private:
	string state;
};

class Caretaker
{
public:
	vector<Memo *> memo;
	void save(Memo *memo)
	{
		(this->memo).push_back(memo);
	}
	Memo *getState(int i)
	{
		return memo[i];
	}
};

int main()
{
	Originator *og=new Originator();
	Caretaker *ct=new Caretaker();

	og->setState("on");
	og->show();
	ct->save(og->createMemo());

	og->setState("off");
	og->show();
	ct->save(og->createMemo());

	og->setState("middle");
	og->show();
	ct->save(og->createMemo());

	og->setMemo( ct->getState(1) );
	og->show();

	return 0;
}

