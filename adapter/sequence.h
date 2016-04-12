#ifndef SEQUENCE_H
#define SEQUENCE_H


class Sequence
{
public:
    Sequence();
public:
    virtual void push(int x) = 0;
    virtual void pop()=0;
};

#endif // SEQUENCE_H
