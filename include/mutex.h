
#ifndef __MUTEX_H__
#define __MUTEX_H__

struct Mutex
{
public:
    Mutex() :
        m_locked(false)
    { /* do nothing */ }

public:
    void lock()
    {
        while (m_locked)
        { /* do nothing */ }

        m_locked = true;
    }

    void unlock()
    {
        m_locked = false;
    }

private:
    bool m_locked;

};

class Lock
{
public:
    Lock(Mutex& mutex) :
        m_mutex_ref(mutex)
    {
        m_mutex_ref.lock();
    }
    virtual ~Lock()
    {
        m_mutex_ref.unlock();
    }

private:
    Mutex& m_mutex_ref;

};

#endif
