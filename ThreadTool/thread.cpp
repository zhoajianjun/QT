#include "thread.h"
#include "app.h"

Thread::Thread()
{
stopped=false;
}

Thread::~Thread()
{

}

void Thread::stop()
{
    stopped=true;
}

void Thread::run()
{
    while(!stopped){
        mutex.lock();
        if (App::list.count()>0){            
            QString txt=App::list.takeFirst();
            emit readOne(txt);
        }
        mutex.unlock();
        msleep(1);//不加这句CPU占用率高达50%
    }
    stopped=false;
}

