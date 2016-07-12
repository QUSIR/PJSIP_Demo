#include "Lock.h"

Lock::Lock(void)
{
	MUTEX_INIT(&m_lock);
}
Lock::~Lock(void)
{
	MUTEX_DESTROY(&m_lock);
}
void Lock::lock()
{
	MUTEX_LOCK(&m_lock);
}
void Lock::unlock()
{
	MUTEX_UNLOCK(&m_lock);
}
