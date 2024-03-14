
#ifndef __ROB_COMMAND_H__
#define __ROB_COMMAND_H__

#include "common.h"
#include "vector.h"
#include "inverseKinematic.h"

enum MoveType : uint8_t
{
    // calculates a line of points, drives to each one
    Linear,
    // calculates two points, lerps between them
    Optimal
};

struct RobCommand
{
    MoveType   moveType;
    uint16_t   speed;
    RobPosition target;
};

#endif
