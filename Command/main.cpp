#if 0
#include <iostream>

using namespace std;

class Command
{
public:
    virtual ~Command();
    virtual void Execute()=0;
protected:
    Command();
private:
};

class Receiver;

class ConcreteCommand : public Command
{
public:
    ConcreteCommand(Receiver* pReceiver);
    ~ConcreteCommand();
    virtual void Execute();
protected:
private:
    Receiver* _recv;
};

class Invoker
{
public:
    Invoker(Command* pCommand);
    ~Invoker();
    void Invoke();
protected:
private:
    Command* _cmd;
};

class Receiver
{
public:
    Receiver();
    ~Receiver();
    void Action();
protected:
private:
};
Command::Command()
{}

Command::~Command()
{}

ConcreteCommand::ConcreteCommand(Receiver* pReceiver)
{
    this->_recv = pReceiver;
}

ConcreteCommand::~ConcreteCommand()
{}

void ConcreteCommand::Execute()
{
    this->_recv->Action();
}

Receiver::Receiver()
{}

Receiver::~Receiver()
{}

void Receiver::Action()
{
    cout << "Receiver::Action" << endl;
}

Invoker::Invoker(Command* pCommand)
{
    this->_cmd = pCommand;
}

Invoker::~Invoker()
{}

void Invoker::Invoke()
{
    this->_cmd->Execute();
}

int main()
{
    cout << "Hello World!" << endl;
    //创建具体命令对象pCmd并设定它的接收者pRev
    Receiver* pRev = new Receiver();
    Command* pCmd = new ConcreteCommand(pRev);
    //请求绑定命令
    Invoker* pInv = new Invoker(pCmd);
    pInv->Invoke();
    return 0;
}
#endif
#include <iostream>
#include <vector>
using namespace std;


// 烤肉师傅
class RoastCook
{
public:
    void MakeMutton() { cout << "烤羊肉" << endl; }
    void MakeChickenWing() { cout << "烤鸡翅膀" << endl; }
};


// 抽象命令类
class Command
{
public:
    Command(RoastCook* temp) { receiver = temp; }
    virtual void ExecuteCmd() = 0;

protected:
    RoastCook* receiver;
};

// 烤羊肉命令
class MakeMuttonCmd : public Command
{
public:
    MakeMuttonCmd(RoastCook* temp) : Command(temp) {}
    virtual void ExecuteCmd() { receiver->MakeMutton(); }
};

// 烤鸡翅膀命令

class MakeChickenWingCmd : public Command
{
public:
    MakeChickenWingCmd(RoastCook* temp) : Command(temp) {}
    virtual void ExecuteCmd() { receiver->MakeChickenWing(); }
};

// 服务员类
class Waiter
{
public:
    void SetCmd(Command* temp);

    // 通知执行
    void Notify();
protected:
    vector<Command*> m_commandList;
};

void Waiter::SetCmd(Command* temp)
{
    m_commandList.push_back(temp);
    cout << "增加订单" << endl;
}

void Waiter::Notify()
{
    vector<Command*>::iterator it;
    for (it=m_commandList.begin(); it!=m_commandList.end(); ++it)
    {
        (*it)->ExecuteCmd();
    }
}

int main()
{
    // 店里添加烤肉师傅、菜单、服务员等顾客
    RoastCook* cook = new RoastCook();
    Command* cmd1 = new MakeMuttonCmd(cook);
    Command* cmd2 = new MakeChickenWingCmd(cook);
    Waiter* girl = new Waiter();

    // 点菜
    girl->SetCmd(cmd1);
    girl->SetCmd(cmd2);

    // 服务员通知
    girl->Notify();
    return 0;
}

