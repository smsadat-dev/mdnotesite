#include <iostream>

#include "mdparser.hpp"

std::string parseHeaders(std::string content)
{
    size_t headingLevel = 0;
    std::string output = "", text = "";
    std::cout << "\nRecieved: " + content;  // debug

    while(headingLevel < content.size() && content[headingLevel] == '#')
    {
        ++headingLevel;
    }
    if(headingLevel >= 1 && headingLevel <= 6 && (content[headingLevel] == ' '))
    {
        text = content.substr(headingLevel + 1);
        output = "<h" + std::to_string(headingLevel) + '>' + text + "</h" + std::to_string(headingLevel) + '>' + '\n';
    }
    else 
    {
        output = content;
    }
    return output;
}