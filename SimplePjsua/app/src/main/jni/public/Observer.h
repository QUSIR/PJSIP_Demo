#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
    virtual ~Observer();
    virtual void onMsgStatus(int status)=0;
protected:
    Observer();
private:
};

#endif // OBSERVER_H
