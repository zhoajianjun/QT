#include <thread>
#include<iostream>
#include<vector>

using namespace std;
using namespace std::this_thread;

void msg()
{
    //MessageBoxA(0, "12345", "678910", 0);
}
void msgA(int num)
{
    std::cout << get_id() << "  num=   " << num << std::endl;
}

int main()
{

    // thread::hardware_concurrency线程
    auto n = thread::hardware_concurrency();
    std::cout << n << std::endl;
    //获取当前线程编号
    std::cout << "thread=" << get_id() << std::endl;


    thread thread1(msg);//创建多线程
    thread thread2(msg);
    thread1.join();//开始执行
    thread2.join();
    std::cin.get();
}

void main2()
{

    vector<thread *> threads;
    for (int i = 0; i < 10; i++)
    {
        threads.push_back(new thread(msg));//创建线程
    }

    for (auto th : threads)
    {
        th->join();
    }

    std::cin.get();





}
int main1()
{

    vector<thread *> threads;
    for (int i = 0; i < 10; i++)
    {
        threads.push_back(new thread(msgA,i));//创建线程
    }

    for (auto th : threads)
    {
        th->join();
    }

    std::cin.get();
}

