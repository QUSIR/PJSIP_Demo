#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include "Observer.h"

using std::list;

class Subject
{
public:
    virtual ~Subject();
    virtual void attach(Observer*);
    virtual void detach(Observer*);
    virtual void msgStatus(int status);
protected:
    Subject();
private:
    list<Observer*> m_lst;
};

#endif // SUBJECT_H
