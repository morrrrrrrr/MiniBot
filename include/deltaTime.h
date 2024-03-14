
#ifndef __TIME_H__
#define __TIME_H__

#include "common.h"

class Time
{
public:
    Time() :
        m_lastTime(millis())
    { /* do nothing */ }
    
public:
    void update()
    {
        m_delta = millis() - m_lastTime;
        m_lastTime = millis();
    }

    int getDelta()
    {
        return m_delta;
    }

private:
    unsigned long m_lastTime;
    int m_delta;
};

#endif
