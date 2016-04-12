#include <iostream>
#include "os.h"
#include "windowos.h"
#include "linuxos.h"
#include "compute.h"
#include "dellcompute.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    Os *os1=new WindowOS();
    Os *os2=new LinuxOs();
    Compute *compute=new DellCompute();
    compute->InstallOs(os1);
    compute->InstallOs(os2);
    return 0;
}

