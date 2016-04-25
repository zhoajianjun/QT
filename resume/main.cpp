#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
class Resume
{
protected:
    char*name;
public:
    Resume(){}
    virtual ~Resume(){}
    virtual Resume*Clone(){return NULL;}
    virtual void Set(char *n){}
    virtual void Show(){}
};
class ResumeA:public Resume
{
public:
    ResumeA(const char*str);
    ResumeA(const ResumeA &r);
    ~ResumeA();
    ResumeA* Clone();
    void Show();
};


ResumeA::ResumeA(const char *str)
{
    if(str==NULL)
    {
        name=new char[strlen(str)+1];
        name[0]='\0';

    }
    else{
        name=new char[strlen(str)+1];
        strcpy(name,str);
    }
}

ResumeA::ResumeA(const ResumeA &r)
{
    name=new char[strlen(r.name)+1];
    strcpy(name,r.name);
}

ResumeA::~ResumeA()
{
    delete []name;
}

ResumeA *ResumeA::Clone()
{
    return new ResumeA(*this);
}

void ResumeA::Show()
{
    cout<<"ResumeA name:"<<name<<endl;
}
int main()
{
    ResumeA *r1=new ResumeA("A");
    ResumeA *r2=new ResumeA("B");


    ResumeA *r3=r1->Clone();
    ResumeA *r4=r2->Clone();
    delete r1;
    r1=NULL;
    delete r2;
    r2=NULL;
    r3->Show();
    r4->Show();
    delete r3;
    delete r4;
    r3=NULL;
    r4=NULL;
    return 0;
}



