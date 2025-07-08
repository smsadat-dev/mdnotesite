#ifndef MDPARSER_HPP
#define MDPARSER_HPP

#include <string>

class MarkdownParser 
{
public:
    std::string parse(const std::string& mdcontent);
};

std::string parseBoldText(std::string content);
std::string parseBoldandItalic(std::string content);
std::string parseCode(std::string content);
std::string parseHeaders(std::string content);
std::string parseHrules(std::string content);
std::string imageParser(std::string content);
std::string parseLink(std::string content);
std::string parseItalicText(std::string content);

#endif // MDPARSER_HPP