#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>


class Deque
{
public:
    Deque();
public:
    void push_back(int x){std::cout<<"Deque push_back"<<std::endl;}
    void push_front(int x){std::cout<<"Deque push_front"<<std::endl;}
    void pop_back() {std::cout<<"deque pop_back"<<std::endl;}
    void pop_front() {std::cout<<"deque pop_front"<<std::endl;}
};

#endif // DEQUE_H
