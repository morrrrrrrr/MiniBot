
#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "common.h"
#include "queue.h"
#include "robCommand.h"
#include "inverseKinematic.h"

class Robot
{


private:
    Queue<RobCommand, 10> m_commandQueue;
    float m_commandProgress;
    
};

#endif
