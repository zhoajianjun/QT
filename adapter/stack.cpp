#include "stack.h"

Stack::Stack()
{

}

void Stack::push(int x)
{
    deque.push_back(x);
}

void Stack::pop()
{
    deque.pop_back();
}

