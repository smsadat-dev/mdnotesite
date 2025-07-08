#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>

#include "mdparser.hpp"

int main(int argc, char const *argv[])
{
    std::string fileName = "index.html";
    MarkdownParser parser;
    std::string content = 
        "# Hello\n"
        "This is a paragraph.\n"
        "## Subheading __This is bold text__ \n"
        "**This is too**\n" 
        "***\n"
        "### Subsubheading\n"
        "*This is italic*\n"
        "_This is also italic_\n"
        "___\n"
        "```print(\"Whatever possible\");```\n"
        "___Bold italic text___\n"
        "***another bold italic text***\n"
        "---\n"
        "![A cute cat](https://example.com/cat.jpg)\n"
        "[OpenAI](https://openai.com \"OpenAI's website\")\n";

    std::cout << "main() called\n Input:\n" + content;
    std::string output = 
        "<!DOCTYPE html>\n<html>\n<head>\n<title>Markdown Preview</title>\n</head>\n<body>\n"
        + parser.parse(content) 
        +  "</body>\n</html>";
    
    std::cout << output  << '\n';

    std::ofstream file(fileName);

    if(!file)
    {
        std::cerr << "Error opening file: " + fileName + '\n';
        perror("");
        return 1;
    }

    file << output;
    file.close();

    std::cout << "HTML output written to " + fileName + '\n';

    std::string commad = "xdg-open " + fileName;
    const char* launchCode =  commad.c_str(); 
    std::system(launchCode);

    return 0;
}

