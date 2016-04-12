#ifndef CACHE_H
#define CACHE_H
#include "replacealgorithm.h"

enum RA {LRU,FIFO };
class Cache
{
public:
    Cache(enum RA ra);
    ~Cache();
public:
    void Replace();

private:
    ReplaceAlgorithm *m_ra;
};

#endif // CACHE_H
