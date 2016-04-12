#include <iostream>
#include <list>
#include <iterator>

using namespace std;
class Company{
public:
    Company(string name){m_name=name;}
    virtual ~Company(){}
    virtual void  Add(Company *pCom){}
    virtual void Show(int depth){}
protected:
    string m_name;
};
class ConcreateCompany:public Company
{
public:
    ConcreateCompany(string name):Company(name){}
    virtual ~ConcreateCompany(){}
    void Add(Company *pCom){m_listCompany.push_back(pCom);}
    void Show(int depth)
    {
        for(int i = 0;i< depth;i++)
            cout<<"-";
        list<Company*>::iterator iter=m_listCompany.begin();
        for(;iter != m_listCompany.end();iter++)
            (*iter)->Show(depth+2);
    }
private:
    list<Company *> m_listCompany;
};
class FinanceDepartment : public Company
{
public:
    FinanceDepartment(string name):Company(name){}
    virtual ~FinanceDepartment() {}
    virtual void Show(int depth) //只需显示，无限添加函数，因为已是叶结点
    {
        for(int i = 0; i < depth; i++)
            cout<<"-";
        cout<<m_name<<endl;
    }
};
//具体的部门，人力资源部
class HRDepartment :public Company
{
public:
    HRDepartment(string name):Company(name){}
    virtual ~HRDepartment() {}
    virtual void Show(int depth) //只需显示，无限添加函数，因为已是叶结点
    {
        for(int i = 0; i < depth; i++)
            cout<<"-";
        cout<<m_name<<endl;
    }
};
int main()
{
    cout << "Hello World!" << endl;
    Company *root=new ConcreateCompany("com");
    Company *leaf1=new FinanceDepartment("fin");
    Company *leaf2=new HRDepartment("hrd");
    root->Add(leaf1);
    root->Add(leaf2);
    root->Show(0);
    cout<<100%9<<endl;

    return 0;
}

