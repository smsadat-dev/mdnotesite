#include "mdparser.hpp"

std::string parseStrike(std::string content)
{
    size_t i = 0;
    std::string output = "";

    while (i < content.size())
    {
        if(content[i] == '~' && content[i+1] == '~')
        {
            std::string marker = "~~";
            size_t highlightStart = i+2;

            size_t highlightEnd = content.find(marker, highlightStart);

            if(highlightEnd != std::string::npos)
            {
                std::string highlightText = content.substr(highlightStart, highlightEnd - highlightStart);
                output += "<del>" + highlightText + "</del>";
                i = highlightEnd + 2;   // jump whole text
            }
            else 
            {
                // No closing '~~', treat as plain text
                output += content[i];
                i++;
            }
        }
        else 
        {
            output += content[i];
            i++;
        }
    }
    return output;
}