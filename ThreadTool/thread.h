#ifndef TEST_H
#define TEST_H

#include "qthread.h"
#include "qmutex.h"

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();
    ~Thread();

    void stop();

protected:
    void run();

private:
    QMutex mutex;
    volatile bool stopped;

signals:
    void readOne(QString txt);

};

#endif // TEST_H
