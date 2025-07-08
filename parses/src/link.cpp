#include <iostream>

#include "mdparser.hpp"

std::string parseLink(std::string content)
{
    size_t i = 0;
    std::string output = "";

    while(i < content.size())
    {
        if(content[i] == '[')
        {
            size_t linkNameStart = i+1;
            size_t linkNameEnd = content.find(']', i);

            if(linkNameEnd != std::string::npos && content[linkNameEnd + 1] == '(')
            {
                size_t urlStart = linkNameEnd + 1;
                size_t urlEnd = content.find(' ', urlStart);

                if(urlEnd != std::string::npos)
                {

                    size_t titleStart = content.find("\"", urlStart);       
                    if(titleStart != std::string::npos)
                    {
                        size_t titleEnd = content.find("\"", titleStart+1);
                        std::string linkName = content.substr(linkNameStart, linkNameEnd - linkNameStart);
                        std::string url = content.substr(urlStart + 1, urlEnd - (urlStart+1));
                        std::string title = content.substr(titleStart, titleEnd - titleStart);
                        output += "<a href=\"" + url + "\" title=\"" + title + "\">" + linkName + "</a>";
                        std::cout << "The output is: " << output << '\n';
                        
                        // jump the whole link 

                        i = content.find(')', titleEnd);
                        if(i != std::string::npos)
                        {
                            i += 1;
                        }
                        else 
                        {
                            ++i;
                        }
                    }
                    else 
                    {
                        std::string linkName = content.substr(linkNameStart, linkNameEnd - linkNameStart);
                        std::string url = content.substr(urlStart, urlEnd - urlStart);
                        std::string title = "";
                        output += "<a href=\"" + url + "\" title=\"" + title + "\">" + linkName + "</a>";
                        
                        // jump the whole link 

                        i = content.find(')', urlEnd);
                        if(i != std::string::npos)
                        {
                            i += 1;
                        }
                        else 
                        {
                            ++i;
                        }
                    }
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


