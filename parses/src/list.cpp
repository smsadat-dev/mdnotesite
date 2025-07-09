#include <iostream>
#include <regex>
#include <sstream>

#include "mdparser.hpp"

int countLeadingSpaces(const std::string& line) {
    int count = 0;
    for (char c : line) {
        if (c == ' ') count++;
        else break;
    }
    return count;
}


bool isUlistItem(const std::string& line)
{
    return !line.empty() && 
           (line[0] == '*' || line[0] == '+' || line[0] == '-') && 
           line.size() > 1 && line[1] == ' ';
}

bool isOlistItem(const std::string& line)
{
    static std::regex orderedListRegex(R"(^\d+\.\s)");
    return std::regex_search(line, orderedListRegex);
}


// Define listInfo strucuture
struct listInfo {
    bool isOrdered;
    int indentLevel;
    bool liOpen;

    listInfo(bool ordered, int indent) : isOrdered(ordered), indentLevel(indent), liOpen(false) {}
};

// You need these helper functions defined somewhere:
int countLeadingSpaces(const std::string& line);
bool isUlistItem(const std::string& line);
bool isOlistItem(const std::string& line);

std::string parseList(std::string content)
{
    std::istringstream stream(content);
    std::string line;
    std::string output = "";
    std::stack<listInfo> listStack;

    while (std::getline(stream, line))
    {
        int indent = countLeadingSpaces(line);
        std::string trimmed = line.substr(indent);

        bool isUl = isUlistItem(trimmed);
        bool isOl = isOlistItem(trimmed);

        if (isUl || isOl)
        {
            bool ordered = isOl;
            size_t markerLen = ordered ? trimmed.find(' ') + 1 : 2;

            // Close open <li> if same indent
            if (!listStack.empty() && indent == listStack.top().indentLevel && listStack.top().liOpen) {
                output += "</li>";
                listStack.top().liOpen = false;
            }

            // Close lists if indent less than current top
            while (!listStack.empty() && indent < listStack.top().indentLevel) {
                if (listStack.top().liOpen) {
                    output += "</li>";
                    listStack.top().liOpen = false;
                }
                output += listStack.top().isOrdered ? "</ol>" : "</ul>";
                listStack.pop();
            }

            // Open new list if indent greater than current top
            if (listStack.empty() || indent > listStack.top().indentLevel) {
                // Close previous <li> so nested lists are inside it properly
                if (!listStack.empty() && listStack.top().liOpen) {
                    output += "</li>";
                    listStack.top().liOpen = false;
                }
                output += ordered ? "<ol>" : "<ul>";
                listStack.push(listInfo(ordered, indent));
            }
            else if (!listStack.empty() && ordered != listStack.top().isOrdered) {
                // Switch list type at same indent: close old and open new
                output += listStack.top().isOrdered ? "</ol>" : "</ul>";
                listStack.pop();
                output += ordered ? "<ol>" : "<ul>";
                listStack.push(listInfo(ordered, indent));
            }

            // Now safe to add list item and mark liOpen true
            output += "<li>" + trimmed.substr(markerLen);
            listStack.top().liOpen = true;
        }
        else
        {
            // Close all lists before outputting normal line
            while (!listStack.empty()) {
                if (listStack.top().liOpen) {
                    output += "</li>";
                    listStack.top().liOpen = false;
                }
                output += listStack.top().isOrdered ? "</ol>" : "</ul>";
                listStack.pop();
            }
            output += line;
        }
    }

    // Close all open lists at EOF
    while (!listStack.empty()) {
        if (listStack.top().liOpen) {
            output += "</li>";
            listStack.top().liOpen = false;
        }
        output += listStack.top().isOrdered ? "</ol>" : "</ul>";
        listStack.pop();
    }

    return output;
}
