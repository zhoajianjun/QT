#include <iostream>

using namespace std;


class ReplaceAlgorithm
{
public:
    virtual void Replace() = 0;
};
//三种具体的替换算法
class LRU_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
    void Replace() { cout<<"Least Recently Used replace algorithm"<<endl; }
};

class FIFO_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
    void Replace() { cout<<"First in First out replace algorithm"<<endl; }
};
class Random_ReplaceAlgorithm: public ReplaceAlgorithm
{
public:
    void Replace() { cout<<"Random replace algorithm"<<endl; }
};
#if 0
class Cache
{
private:
    ReplaceAlgorithm *m_ra;
public:
    Cache(ReplaceAlgorithm *ra) { m_ra = ra; }
    ~Cache() { delete m_ra; }
    void Replace() { m_ra->Replace(); }
};
#endif

#if 0

enum RA {LRU, FIFO, RANDOM}; //标签
class Cache
{
private:
    ReplaceAlgorithm *m_ra;
public:
    Cache(enum RA ra)
    {
        if(ra == LRU)
            m_ra = new LRU_ReplaceAlgorithm();
        else if(ra == FIFO)
            m_ra = new FIFO_ReplaceAlgorithm();
        else if(ra == RANDOM)
            m_ra = new Random_ReplaceAlgorithm();
        else
            m_ra = NULL;
    }
    ~Cache() { delete m_ra; }
    void Replace() { m_ra->Replace(); }
};

#endif
#if 1
template <class RA>
class Cache
{
private:
    RA m_ra;
public:
    Cache() { }
    ~Cache() { }
    void Replace() { m_ra.Replace(); }
};
#endif
int main()
{
#if 0
    Cache cache(new LRU_ReplaceAlgorithm()); //暴露了算法的定义
    cache.Replace();
#endif
#if 0
    Cache cache(LRU); //指定标签即可
    cache.Replace();
#endif
    Cache<Random_ReplaceAlgorithm> cache; //模板实参
    cache.Replace();
    return 0;
}

