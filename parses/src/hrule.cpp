#include <algorithm>
#include <cctype>
#include <iostream>

#include "mdparser.hpp"

std::string trimws(const std::string& str)
{
    auto start = std::find_if_not(str.begin(), str.end(), ::isspace);
    auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
    return (start < end) ? std::string(start, end)  : "";
}

std::string parseHrules(std::string content)
{
    size_t i = 0;
    std::string output = "";
    size_t lineEnd = 0, lineStart = 0;

    while (i < content.size())
    {

        size_t lineEnd = content.find('\n', i);

        if(lineEnd == std::string::npos)
        {
            lineEnd = content.size();
        }

        std::string line  = content.substr(i, lineEnd - i);
        std::string trimmed = trimws(line);

        if(trimmed == "***" || trimmed == "---" ||  trimmed == "___")
        {
            output += "<hr>";
        }
        else 
        {
            output += line;
        }
        i = lineEnd + 1;
    }

    return output;
}