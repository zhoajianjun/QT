#include <iostream>
/******外观模式******/
using namespace std;
class Scanner
{
public:
    void Scan(){cout<<"cifafenxi"<<endl;}
};
class Parser
{
public:
    void Parsers(){cout<<"yufafenxi"<<endl;}
};
class GenMidCode
{
public:
    void GenCode(){cout<<"code"<<endl;}
};
class GenMachineCode
{
public:
    void GenMaCode(){cout<<"jiqicode"<<endl;}
};
class  Compiler
{
public:
     Compiler() {}
     void Run()
     {
         Scanner s;
         Parser p;
         GenMidCode g;
         GenMachineCode ge;
         s.Scan();
         p.Parsers();
         g.GenCode();
         ge.GenMaCode();
     }
};


int main()
{
    cout << "Hello World!" << endl;
    Compiler c;
    c.Run();
    return 0;
}

