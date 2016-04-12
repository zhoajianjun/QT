#ifndef DELLCOMPUTE_H
#define DELLCOMPUTE_H
#include "compute.h"
#include "os.h"


class DellCompute : public Compute
{
public:
    DellCompute();
    void InstallOs(Os*os);
};

#endif // DELLCOMPUTE_H
