#pragma once

#include "PublicDefine.h"

class Lock
{
public:
	Lock(void);
	~Lock(void);
	void lock();
	void unlock();
private:
	MUTEX_TYPE m_lock;
};
