
#ifndef __STRING_TOOLS_H__
#define __STRING_TOOLS_H__

struct string
{
    char* data;
    int length;
};

namespace tools
{

    int strFind(const string& str, char find, int offset = 0);

} // namespace tools

#endif
