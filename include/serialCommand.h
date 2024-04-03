
#ifndef __SERIAL_COMMAND_H__
#define __SERIAL_COMMAND_H__

#include <Arduino.h>

typedef unsigned char cmd_t;

namespace serial
{

    struct Message
    {
        struct Header
        {
            cmd_t  type;
            size_t size;
        } header;

        void* data;

    public:
        template <typename T>
        Message(cmd_t type, T& data)
        {
            header.type = type;
            header.size = sizeof(T);

            this->data = malloc(header.size);

            memcpy(this->data, &data, header.size);
        }

        Message(cmd_t type, size_t size)
        {
            header.type = type;
            header.size = size;

            data = malloc(size);
        }

        virtual ~Message()
        {
            free(data);
        }

    public:
        void clear()
        {
            header.type = 0;
            header.size = 0;

            free(data);
            data = NULL;
        }

        void resize(size_t newSize)
        {
            if (data == NULL) return;

            header.size = newSize;
            data = malloc(newSize);
        }

    };

} // namespace serial

class SerialCommands
{
public:
    SerialCommands() : 
        m_messageIn(0, 0)
    {

    }

public:
    void update()
    {
        if (Serial.available())
        {
            byte b = Serial.read();

            handleIncomingByte(b);
        }
    }

    void setCallback(void (*callbackFunc)(serial::Message&))
    {
        m_callback = callbackFunc;
    }

private:
    void handleIncomingByte(byte b)
    {
        switch (m_state)
        {
        case State::READ_TYPE:
            m_state = State::READ_SIZE;
            m_progress = 0;

            m_messageIn.header.type = b;

            break;

        case State::READ_SIZE:
            m_messageIn.header.size = (m_messageIn.header.size) | (b >> (m_progress * 8));
            m_progress++;

            if (m_progress >= sizeof(size_t))
            {
                m_state = State::READ_DATA;
                m_progress = 0;
            }
            break;

        case State::READ_DATA:
            m_messageIn.header.size = (m_messageIn.header.size) | (b >> (m_progress * 8));
            m_progress++;

            if (m_progress >= m_messageIn.header.size)
            {
                m_state = State::READ_TYPE;
                handleDoneMessage();
            }
            break;

        default:
            break;
        }
    }

    void handleDoneMessage()
    {
        (*m_callback)(m_messageIn);

        m_messageIn.clear();
    }

private:
    enum State
    {
        READ_TYPE,
        READ_SIZE,
        READ_DATA
    } m_state = State::READ_TYPE;

    serial::Message m_messageIn;
    size_t m_progress = 0;
    
    void (*m_callback)(serial::Message&);

};

#endif
