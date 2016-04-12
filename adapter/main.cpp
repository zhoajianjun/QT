#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    Sequence *s1 = new Stack();
    s1->push(1);s1->pop();
    delete s1;
    return 0;
}

