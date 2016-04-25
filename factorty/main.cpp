#include <iostream>
using namespace std;
enum BASE{BS1,BS2};
class base
{
public:
    base()
    {

    }
    ~base()
    {

    }

    virtual void show ()=0;
};
class base1 : public base
{
public:
    base1()
    {

    }
    ~base1()
    {

    }
    void show()
    {
        cout<<"base1"<<endl;
    }
};

class base2 : public base
{
public:
    base2()
    {

    }
    ~base2()
    {

    }
    void show()
    {
        cout<<"base2"<<endl;
    }

};
class CreateFactory
{
public:
    CreateFactory()
    {

    }
    ~CreateFactory()
    {

    }
    base * createBase(BASE type)
    {
        switch (type) {
        case BS1:
            return new base1;
            break;
        case BS2:
            return new base2;
            break;
        default:
            break;
        }
    }

private:




};




int main()
{
    cout << "Hello World!" << endl;
    CreateFactory factory;
    base* bs1=factory.createBase(BS1);
    bs1->show();
    base* bs2=factory.createBase(BS2);
    bs2->show();
    delete bs1;
    delete bs2;
    return 0;
}

