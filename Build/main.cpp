#include <iostream>

using namespace std;
class Builder{
public:
    virtual void BuilderHeader(){}
    virtual void BuilderBody(){}
    virtual void BuilderLeftArm(){}
    virtual void BuilderRightArm(){}
    virtual void BuilderLeftLeg(){}
    virtual void BuilderRightLeg(){}

};

class ThinBuilder:public Builder
{
public:
    void BuilderHeader(){cout<<" thin header"<<endl;}
    void BuilderBody(){cout<<"thin body"<<endl;}
    void BuilderLeftArm(){cout<<"thin left arm"<<endl;}
    void BuilderRightArm(){cout<<"thin right arm"<<endl;}
    void BuilderLeftLeg(){cout<<"thin left leg"<<endl;}
    void BuilderRightLeg(){cout<<"thin right leg"<<endl;}

};
class FatBuilder :public Builder
{
public:
    void BuilderHeader(){cout<<"fat header"<<endl;}
    void BuilderBody() {cout<<"fat body"<<endl;}
    void BuilderLeftLeg(){cout<<"fat left leg"<<endl;}
    void BuilderRightLeg(){cout<<"fat right leg"<<endl;}
    void BuilderLeftArm(){cout<<"fat left arm"<<endl;}
    void BuilderRightArm(){cout<<"fat right arm"<<endl;}
};
class Director
{
private:
    Builder *m_builder;
public:
    Director(Builder *builder){m_builder=builder;}
    void Create()
    {
        m_builder->BuilderHeader();
        m_builder->BuilderBody();
        m_builder->BuilderLeftArm();
        m_builder->BuilderRightArm();
        m_builder->BuilderLeftLeg();
        m_builder->BuilderRightLeg();
    }
};

int main()
{
    cout << "Hello World!" << endl;
    ThinBuilder thin;
    FatBuilder fat;
    Director director(&fat);
    director.Create();
    return 0;
}

