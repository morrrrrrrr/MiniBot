#include "serialInterface.h"

SerialInterface::SerialInterface()
{ }

void SerialInterface::update()
{
    while (Serial.available())
    {
        char c = Serial.read();

        switch (c)
        {
        case MSG_END_CHAR:
            messageEnd();
            break;

        default:
            appendChar(c);
            break;
        }
    }
}

void SerialInterface::setCallback(void (*onMessageReceived)(string))
{
    m_messageReceivedCallback = onMessageReceived;
}

void SerialInterface::appendChar(char c)
{
    if (getCurrentMessageSize() >= BUFFER_SIZE)
    {
        handle_robot_error(rob_error_t::SERIAL_MESSAGE_BUFFER_OVERFLOW);
    }

    *m_currentPos = c;
    m_currentPos++;
}

void SerialInterface::messageEnd()
{
    
    resetBuffer();
}

void SerialInterface::resetBuffer()
{
    m_currentPos = m_buffer;
}

int SerialInterface::getCurrentMessageSize()
{
    return m_currentPos - m_buffer;
}
