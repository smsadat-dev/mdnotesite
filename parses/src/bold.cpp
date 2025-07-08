#include "mdparser.hpp"

std::string parseBoldText(std::string content)
{
    std::string output = "";
    size_t i = 0;

    while(i < content.size())
    {
        if(
            (i + 1) < content.size() &&
            ((content[i] == '*' && content[i+1] == '*') || 
            (content[i] == '_' && content[i+1] == '_'))
        )
        {
            std::string marker = content.substr(i, 2);
            i += 2;

            size_t end = content.find(marker, i);

            if(end != std::string::npos)
            {
                std::string boldText = content.substr(i, end - i);
                output += "<strong>" + boldText + "</strong>";
                i = end + 2;
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