#ifndef CACHE1_H
#define CACHE1_H

template <class RA>
class Cache1
{
public:
    Cache1(RA ra);
    ~Cache1();
public:
    void Replace();
private:
    RA m_ra;
};

#endif // CACHE1_H
