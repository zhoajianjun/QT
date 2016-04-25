#include <iostream>

using namespace std;

class Manger
{

public:
    Manger(Manger *manger,string name):m_manger(manger),m_name(name){}
    virtual void DealRequest(string name,int num){}
protected:
    Manger *m_manger;
    string m_name;

};

class CommonManger : public Manger
{
public:
    CommonManger(Manger *manger,string name):Manger(manger,name){}
    void DealRequest(string name,int num)
    {
        if(num < 500) //经理职权之内
            {
                cout<<"经理"<<m_name<<"批准"<<name<<"加薪"<<num<<"元"<<endl<<endl;
            }
            else
            {
                cout<<"经理"<<m_name<<"无法处理，交由总监处理"<<endl;
                m_manger->DealRequest(name, num);
            }
    }
};
class Majordomo: public Manger
{
public:
    Majordomo(Manger *manger, string name):Manger(manger,name) {}
    void DealRequest(string name, int num)
    {
        if(num < 1000) //总监职权之内
        {
            cout<<"总监"<<m_name<<"批准"<<name<<"加薪"<<num<<"元"<<endl<<endl;
        }
        else
        {
            cout<<"总监"<<m_name<<"无法处理，交由总经理处理"<<endl;
            m_manger->DealRequest(name, num);
        }
    }
};
//总经理
class GeneralManager: public Manger
{
public:
    GeneralManager(Manger *manger, string name):Manger(manger,name) {}
    void DealRequest(string name, int num)  //总经理可以处理所有请求
    {
        cout<<"总经理"<<m_name<<"批准"<<name<<"加薪"<<num<<"元"<<endl<<endl;
    }
};

int main()
{
    Manger *general = new GeneralManager(NULL, "A"); //设置上级，总经理没有上级
    Manger *majordomo = new Majordomo(general, "B"); //设置上级
    Manger *common = new CommonManger(majordomo, "C"); //设置上级
    common->DealRequest("D",300);   //员工D要求加薪
    common->DealRequest("E", 600);
    common->DealRequest("F", 1000);
    delete common; delete majordomo; delete general;
    cout << "Hello World!" << endl;
    return 0;
}

