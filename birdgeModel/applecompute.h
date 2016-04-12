#ifndef APPLECOMPUTE_H
#define APPLECOMPUTE_H
#include "compute.h"
#include "os.h"


class AppleCompute : public Compute
{
public:
    AppleCompute();
    void InstallOs(Os *os);

};

#endif // APPLECOMPUTE_H
