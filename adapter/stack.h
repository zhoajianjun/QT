#ifndef STACK_H
#define STACK_H
#include "sequence.h"
#include "deque.h"

class Stack:public Sequence
{
public:
    Stack();
public:
    void push(int x);
    void pop();
private:
    Deque deque;

};

#endif // STACK_H
