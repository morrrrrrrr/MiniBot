
#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "robotCommand.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

struct Data
{
    void*    data;
    uint16_t size;
};

class Program
{
public:
    Program()
    { }

    virtual ~Program()
    {
        if (m_commands)
        {
            free(m_commands);
        }
    }

public:
    Data serialize()
    {
        Data data;

        data.size = this->sizeBytes();
        data.data = malloc(data.size);

        memcpy(data.data, &m_size, sizeof(m_size));
        memcpy((void*)((char*)data.data + sizeof(m_size)), m_commands, m_size * sizeof(RobCommand));

        return data;
    }

    void deserialize(Data data)
    {
        uint16_t size;

        // read size
        memcpy(&size, data.data, sizeof(m_size));

        resize(size);

        memcpy(m_commands, (void*)((char*)data.data + sizeof(m_size)), size * sizeof(RobCommand));
    }

public:
    RobCommand* data()
    {
        return m_commands;
    }

    uint16_t size() const
    {
        return m_size;
    }

    uint16_t sizeBytes() const
    {
        return m_size * sizeof(RobCommand) + sizeof(m_size);
    }

public:
    RobCommand* current()
    {
        return m_programPointer;
    }

    RobCommand* step()
    {
        m_programPointer++;
        
        if (m_programPointer - m_commands >= m_size)
        {
            reset();
        }

        return current();
    }

    void reset()
    {
        m_programPointer = m_commands;
    }

public:
    void clear()
    {
        resize(0, true);
    }

public:
    void resize(uint16_t newSize, bool clear = false)
    {
        RobCommand* newData = (RobCommand*)malloc(newSize * sizeof(RobCommand));

        if (!clear)
        {
            memcpy(newData, m_commands, MIN(m_size, newSize));
        }

        if (m_commands)
        {
            free(m_commands);
        }

        m_commands = newData;
        m_size = newSize;

        reset();
    }

private:
    uint16_t    m_size = 0;
    RobCommand* m_commands = NULL;

    RobCommand* m_programPointer = NULL;

};

#endif
