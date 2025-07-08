#include "mdparser.hpp"

std::string parseCode(std::string content)
{
    std::string output = "";
    size_t i = 0;
    
    while (i < content.size())
    {
        
        if(
            ((i +2) < content.size()) &&
            (content[i] == '`' && content[i+1] == '`' && content[i+2] == '`')
        )
        {
            std::string marker = content.substr(i, 3);   
            i += 3;

            size_t end = content.find(marker, i);

            if(end != std::string::npos)
            {
                std::string codeText = content.substr(i, end - i);
                output += "<pre><code>" + codeText + "</code></pre>";
                i = end + 3;
            }
            else 
            {
                output += marker;
            }
        }
        else if(
            (i < content.size()) && (content[i] == '`') 
        )
        {
            std::string marker = content.substr(i, 1);   
            i += 1;

            size_t end = content.find(marker, i);

            if(end != std::string::npos)
            {
                std::string codeText = content.substr(i, end - i);
                output += "<code>" + codeText + "</code>";
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