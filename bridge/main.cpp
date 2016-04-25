#include <iostream>

using namespace std;

class OS
{
public:
    virtual void InstallOS_Imp() {}
};
class WindowOS: public OS
{
public:
    void InstallOS_Imp() { cout<<"安装Window操作系统"<<endl; }
};
class LinuxOS: public OS
{
public:
    void InstallOS_Imp() { cout<<"安装Linux操作系统"<<endl; }
};
class UnixOS: public OS
{
public:
    void InstallOS_Imp() { cout<<"安装Unix操作系统"<<endl; }
};
//计算机
class Computer
{
public:
    virtual void InstallOS(OS *os) {}
};
class DellComputer: public Computer
{
public:
    void InstallOS(OS *os) { os->InstallOS_Imp(); }
};
class AppleComputer: public Computer
{
public:
    void InstallOS(OS *os) { os->InstallOS_Imp(); }
};
class HPComputer: public Computer
{
public:
    void InstallOS(OS *os) { os->InstallOS_Imp(); }
};

int main()
{
    OS *os1 = new WindowOS();
    OS *os2 = new LinuxOS();
    OS *os3 = new UnixOS();
    Computer *computer1 = new AppleComputer();
    computer1->InstallOS(os1);
    computer1->InstallOS(os2);
    computer1->InstallOS(os3);
    cout << "Hello World!" << endl;
    return 0;
}

