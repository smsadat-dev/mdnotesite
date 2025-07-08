#include "mdparser.hpp"

std::string parseItalicText(std::string content)
{
    std::string output = "";
    size_t i = 0;

    while(i < content.size())
    {
        if(
            i  < content.size() &&
            ((content[i] == '*') || (content[i] == '_'))
        )
        {
            std::string marker = content.substr(i, 1);
            i += 1;
            
            size_t end = content.find(marker, i);
            
            if(end != std::string::npos)
            {
                std::string boldText = content.substr(i, end - i);
                output += "<em>" + boldText + "</em>";
                i = end + 1;
            }   
            else 
            {
                output += marker;
            }
        }
        else 
        {
            output += content[i];
            ++i;
        }
    }
    return output;
}