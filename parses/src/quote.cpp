#include <sstream>

#include "mdparser.hpp"

std::string parseQuote(std::string content)
{
    std::istringstream stream(content);
    std::string line, output = "";
    std::string startQuote = "<blockquote>", endQuote = "</blockquote>";
    size_t i = 0, quoteLevel = 0;

    while(std::getline(stream, line))
    {
        while(i < line.size() && line[i] == '>')
        {
            quoteLevel++;
            i++;
            if(i < line.size() && line[i] == ' ') i++;
        } 
        
        std::string cleanedLine = line.substr(i);
        
        for(size_t k = 0; k < quoteLevel; k++)
        {
            output += startQuote;
        }
        output +=cleanedLine;
        for(size_t k = 0; k < quoteLevel; k++)
        {
            output += endQuote;
        }
        output += '\n';
    }
    return output;
}