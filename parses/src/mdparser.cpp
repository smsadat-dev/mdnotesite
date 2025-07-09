#include <iostream>
#include <string>
#include <sstream>

#include "mdparser.hpp"


std::string parseLine(std::string line)
{
    std::cout << "\n0th output:\n " + line; // debug

    line = parseHrules(line);
    std::cout << "\n7th output:\n " + line; // debug

    line = parseBoldText(line);      
    std::cout << "\n1st output:\n " + line; // debug

    line = parseCode(line);
    std::cout << "\n2nd output:\n " + line; // debug

    line = parseItalicText(line);
    std::cout << "\n3rd output:\n " + line; // debug

    line = parseBoldandItalic(line);
    std::cout << "\n4th output:\n " + line; // debug

    line = imageParser(line);
    std::cout << "\n5th output:\n " + line; // debug

    line = parseLink(line);
    std::cout << "\n6th output:\n " + line; // debug

    line = parseQuote(line);
    std::cout << "\n8th output:\n " + line; // debug

    line = parseHighlight(line);
    std::cout << "\n9th output:\n " + line; // debug

    line = parseStrike(line);
    std::cout << "\n10th output:\n " + line; // debug

    line = parseList(line);
    std::cout << "\n11th output:\n " + line; // debug

    line = parseHeaders(line);       // Wrap it in header if needed
    std::cout << "\n12th output:\n " + line; // debug
    if (line.empty()) return "";
    return line;
}

std::string MarkdownParser::parse(const std::string& mdcontent)
{
    std::istringstream stream(mdcontent);
    std::string line, html;

    
    while(std::getline(stream, line))
    {
        html += parseLine(line);
    }

    return html;
}