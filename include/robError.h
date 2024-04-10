
#ifndef __ROB_ERROR_H__
#define __ROB_ERROR_H__

#include <Arduino.h>

enum rob_error_t : uint8_t
{
    NO_ERROR = 0,
    OUT_OF_BOUNDS = 100,
    TOO_CLOSE_ANGLES,
    SERIAL_MESSAGE_BUFFER_OVERFLOW = 200
};

static rob_error_t robError = rob_error_t::NO_ERROR;

inline void handle_robot_error(rob_error_t err)
{
    if (err) robError = err;
}
inline bool check_robot_error()
{
    return robError;
}

#endif
