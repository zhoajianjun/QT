#include <iostream>

using namespace std;
class Manger
{
public:
    Manger(Manger*manger,string name):m_manger(manger),m_name(name){}
    virtual void add(string name,int num)
    {

    }

protected:
    Manger *m_manger;
    string m_name;
};
class CommonManger:public Manger
{
public:
    CommonManger(Manger* mang,string name):Manger(mang,name)
    {

    }
    void add(string name, int num)
    {
        if(num<500)
        {
            cout<<"tongyi"<<endl;
        }
        else
        {
            m_manger->add(name,num);
        }
    }

};
class MajorManger:public Manger
{
public:
    MajorManger(Manger *mang,string name):Manger(mang,name)
    {

    }
    void add(string name,int num)
    {
        if(num<1000)
        {
            cout<<"BB"<<endl;
        }
        else
        {
            m_manger->add(name,num);
        }
    }
};
class GeneralManger:public Manger
{
public:
    GeneralManger(Manger *mang,string name):Manger(mang,name)
    {

    }
    void add(string name, int num)
    {
      cout<<"aa"<<endl;
    }
};


int main()
{
    Manger *gen=new GeneralManger(NULL,"A");
    Manger *majordomo = new MajorManger(gen, "B"); //设置上级
    Manger *common = new CommonManger(majordomo, "C"); //设置上级
    common->add("D",300);   //员工D要求加薪
    common->add("E", 600);
    common->add("F", 1000);
    cout << "Hello World!" << endl;
    return 0;
}

