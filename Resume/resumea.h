#ifndef RESUMEA_H
#define RESUMEA_H
#include "resume.h"


class ResumeA : public Resume
{
public:
    ResumeA(const char *str);
    ResumeA(const ResumeA &r);
    ~ResumeA();
public:
    ResumeA* Clone();
    void Show();
};

#endif // RESUMEA_H
