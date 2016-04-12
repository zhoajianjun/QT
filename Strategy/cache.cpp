#include "cache.h"
#include <iostream>
#include "lrureplacealgorithm.h"
#include "fiforeplacealgorithm.h"

Cache::Cache(RA ra)
{
    if(ra==LRU)
        m_ra=new LruReplaceAlgorithm();
    else if(ra==FIFO)
        m_ra=new FifoReplaceAlgorithm();
    else
        m_ra=NULL;
}

Cache::~Cache()
{
    delete m_ra;
}

void Cache::Replace()
{
    m_ra->Replace();
}



