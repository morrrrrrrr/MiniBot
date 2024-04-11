#include "stringTools.h"

void string::move(int len)
{
    if (length - len < 0)
        len = length;

    data += len;
    length -= len;
}

int tools::strFind(const string& str, char find, int offset)
{
    const char* ptr = (str.data + offset);
    while (*ptr != find && ptr - str.data < str.length)
    {
        ptr++;
    }
    return ptr - str.data;
}
