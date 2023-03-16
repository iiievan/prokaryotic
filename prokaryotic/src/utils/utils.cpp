#include "utils/utils.h"

std::string operator-(std::string source, const std::string& target)
{
    for (size_t pos, size{ target.size() }; (pos = source.find(target)) != std::string::npos; )
    {
        source.erase(source.cbegin() + pos,
        source.cbegin() + (pos + size));
    }

    return source;
}