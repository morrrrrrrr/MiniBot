
/*
 * In addition to being completely awesome, this queue is also thread-locked!
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "mutex.h"

template <typename T, int maxSize>
class Queue
{
public:
    Queue()
    {
        m_head = m_root;
        m_root = m_head;
    }

public:
    int getMaxSize() const
    {
        return maxSize;
    }

    int getSize() const
    {
        if (m_head <= m_root)
        {
            return (m_data + maxSize - m_root) + (m_head - m_data);
        }

        return (m_head - m_data) - (m_root - m_data);
    }

private:
    void increment(T*& ptr)
    {
        if (ptr - m_data >= maxSize)
        {
            ptr = m_data;
        }

        ptr++;
    }

public:
    T peek_front()
    {
        // Error-Handling: size is 0:
        if (m_root == m_head)
        {
            return T{};
        }

        return *m_root;
    }
    T pop_front()
    {
        Lock lock(m_mutex);

        // Error-Handling: size is 0:
        if (m_root == m_head)
        {
            return T{};
        }

        T rootData = *m_root;

        increment(m_root);

        return rootData;
    }
    
public:
    void push_back(const T& data)
    {
        Lock lock(m_mutex);

        // Error-Handling: 
        if (m_head + 1 == m_root)
        {
            return;   
        }

        increment(m_head);

        *m_head = data;
    }

private:
    T* m_head;
    T* m_root;
    T  m_data[maxSize];

    Mutex m_mutex;

};

#endif
