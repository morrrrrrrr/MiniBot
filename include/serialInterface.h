
#ifndef __SERIAL_INTERFACE_H__
#define __SERIAL_INTERFACE_H__

#include <Arduino.h>
#include "robError.h"
#include "stringTools.h"

#define BUFFER_SIZE 512
#define MSG_END_CHAR '\n'

class SerialInterface
{
public:
    SerialInterface();

public:
    void update();

    void setCallback(void (*onMessageReceived)(string));

private:
    void appendChar(char c);

    void messageEnd();

    void resetBuffer();

private:
    int getCurrentMessageSize();

private:
    char  m_buffer[BUFFER_SIZE];
    char *m_currentPos;

    void (*m_messageReceivedCallback)(string);

};

#endif
