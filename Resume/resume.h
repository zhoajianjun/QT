#ifndef RESUME_H
#define RESUME_H


class Resume
{
public:
    Resume();
    virtual ~Resume();
public:
    virtual Resume*Clone(){return 0;}
    virtual void Set(char *n);
    virtual void Show();
protected:
    char *name;
};

#endif // RESUME_H
