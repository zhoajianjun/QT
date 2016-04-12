#ifndef COMPUTE_H
#define COMPUTE_H
#include "os.h"


class Compute
{
public:
    Compute();
    virtual void InstallOs(Os *os);
};

#endif // COMPUTE_H
