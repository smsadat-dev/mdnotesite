#include "mdparser.hpp"

std::string imageParser(std::string content)
{
    std::string output = "";
    size_t i = 0;
    while (i < content.size())
    {
        if(content[i] == '!' && content[i+1] == '[')
        {
            size_t altstart = i + 2;
            size_t altend = content.find(']', altstart);
            
            if(altend != std::string::npos && content[altend + 1] == '(')
            {
                size_t urlstart = altend + 2;
                size_t urlend = content.find(')', urlstart);
                
                if(urlend != std::string::npos)
                {
                    std::string altText = content.substr(altstart, altend - altstart);
                    std::string urlText = content.substr(urlstart, urlend - urlstart);
                    output += "<img src=\"" + urlText + "\" " + "alt=\"" + altText + "\">";
                    i = urlend + 1; // jump entire image syntax
                }
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