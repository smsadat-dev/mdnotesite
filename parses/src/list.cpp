#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "mdparser.hpp"

#define ULISTMARKERLEN 2
#define OLISTMARKERLEN 3

#define OLISTITEM 1 // an ordered list item
#define ULISTITEM 2 // an unordered list item
#define NLISTITEM -1 // not a list item

constexpr int INDENT_UNIT = 4;

struct listState 
{
    bool isList;
    bool isOrdered;
    bool isParentOrdered;
    /*
    listIndentation = 0 means not a list item
    listIndentation = 1 means 1st level of list or plain list
    and goes on
    */
   float listIndentation = 1; 
   bool endOfList;
   bool endOfstream;
};

struct stateRecorder
{
    bool isParentOrdered;
    std::string past;
    std::string present;
    std::string future;
};
stateRecorder record;

struct streamRecorder
{
    std::string m_line;
    int m_listType;
    bool m_nested;

    streamRecorder(std::string line, int listType, bool nested) 
    : m_line(line), m_listType(listType), m_nested(nested) {}
};

std::vector<streamRecorder> sr;


int lineCounter = -1;
int olistCounter = 1;

struct lineDescriptor
{
    std::string listifiedLine;
    int indentation;
    int itemType;
    bool nested;
};


std::string trimLeadingWhspace(std::string line)
{
    int countws = 0;
    for(char c : line)
    {
        if(isspace(c))
        {
            countws++;
        }
        else
        {
            break;
        }
    }
    return line.substr(countws);
}


bool isUlistItem(std::string line)
{

    std::string trim = trimLeadingWhspace(line);

    return (!trim.empty() && 
           (trim[0] == '*' || trim[0] == '+' || trim[0] == '-') && 
           trim.size() > 1 && trim[1] == ' ');
}

bool isOlistItem(std::string line)
{
    std::string trim = trimLeadingWhspace(line);
    static std::regex orderedListRegex(R"(^\d+\.\s)");
    return std::regex_search(trim, orderedListRegex);
}

std::string trimListMarker(std::string line)
{
    if(isOlistItem(line))
    {
        line = line.substr(OLISTMARKERLEN);
    }
    else if(isUlistItem(line))
    {
        line = line.substr(ULISTMARKERLEN);
    }
    return line;
}

bool checkEndOfList(std::string nextLine)
{
    // if next line is not a list item then current line is end of list
    if(!isOlistItem(nextLine) && !isUlistItem(nextLine))
    {
        return true;   
    }
    return false;
}

bool isNestedItem(std::string line)
{
    if (line.empty()) return false;
    if (line[0] == '\t') return true;
    if (line.size() < 3) return false;
    return std::isspace(line[0]) && std::isspace(line[1]) && std::isspace(line[2]);
}

std::string stateDescriptor(std::istringstream& stream, listState linestate)
{
    std::string nextLine = "";
    std::streampos pos = stream.tellg(); // save current position
    if (!std::getline(stream, nextLine)) {
        linestate.endOfList = true;
        linestate.endOfstream = true;
    }
    else 
    {
        stream.clear();  // Clear EOF flag if set
        stream.seekg(pos);  // get back to previous position
    }

    return nextLine;
}

float countIndentedWhspaces(std::string listItem)
{
    float counter = 0;
    if(isUlistItem(listItem) || isOlistItem(listItem))
    {
        for(char c : listItem)
        {
            if(c == ' ')
                counter++;
            else if (c == '\t')
                counter += 4; 
            else break;
        }
        return counter;
    }
    return counter;
}

lineDescriptor listifyLine(std::string line, bool ordered)
{
    lineDescriptor ld;
    int countIndentation = countIndentedWhspaces(line);
    std::string trim = trimLeadingWhspace(line);
    trim = "<li>" + trimListMarker(trim) + "</li>";

   // std::cout << "linecounter: " << lineCounter << '\n';
    if(ordered)
    {
        if(countIndentation >= 3)
        {
            // in case of nested list item
            int currentIndent  = countIndentation;
            int prevIndent = countIndentedWhspaces(record.past);
            int nextIndent  = countIndentedWhspaces(record.future);

            if(!sr.at(lineCounter -1).m_nested)
            {  
                // trim "</li></ol>" or "</li></ul>" from previous line if previous line is plain list item              
                sr.at(lineCounter-1).m_line = 
                sr.at(lineCounter-1).m_line.substr(0, sr.at(lineCounter -1).m_line.size() - 10);
                trim = "<ol>" + trim;
            }
            else if(sr.at(lineCounter -1).m_nested)
            {
                // first check if previous nested item itself is parents or not
                if((currentIndent - prevIndent) >= INDENT_UNIT)
                {
                    // deep nesting starts
                    // trim "</li>" or "</li>" from previous line if previous line itself another nested list item but parents
                    sr.at(lineCounter-1).m_line = 
                    sr.at(lineCounter-1).m_line.substr(0, sr.at(lineCounter -1).m_line.size() - 5);
                    trim = "<ol>" + trim;
                }
                if((currentIndent - nextIndent) >= INDENT_UNIT)
                {
                    // deep nesting ends
                    trim = trim + "</ol></li>";
                    std::cout << "Deep nesting ends!\n";
                }
            }

            if(!isNestedItem(record.future))
            {
                /* 
                    check if current nested item is the last item of nested list   
                    to close that parents list
                */
                trim += "</ol></li>";   
                if(isOlistItem(record.future) && !record.isParentOrdered)
                {
                    // if future plain list item is ordered list item but current item's parent is unordered
                    trim +=  "</ul>";
                }
                else if(isUlistItem(record.future) && record.isParentOrdered)
                {
                    // if future plain list item is unordered list item but current item's parent is ordered
                    trim +=  "</ol>";
                }
            }
        }
        else 
        {
            // plain list item

            if(record.isParentOrdered)
            {
                // when there was uninterrupted ordered list already , no need to re-initiate 
                trim = trim + "</ol>";
            }
            else 
            {
                trim = "<ol>" + trim + "</ol>";
            }

            if(isNestedItem(record.future))
            {
                // if next list item is nested then keep record of current list status as parent
                record.isParentOrdered = true;
            }
        }
    }
    else 
    {
        if(countIndentation >= 3)
        {
            // in case of nested list item

            int currentIndent  = countIndentation;
            int prevIndent = countIndentedWhspaces(record.past);
            int nextIndent = countIndentedWhspaces(record.future);

            if(!sr.at(lineCounter -1).m_nested)
            {                
                // trim "</li></ol>" or "</li></ul>" from previous line if previous line is plain list item
                sr.at(lineCounter-1).m_line = 
                sr.at(lineCounter-1).m_line.substr(0, sr.at(lineCounter -1).m_line.size() - 10);
                trim = "<ul>" + trim;
            }
            else if(sr.at(lineCounter -1).m_nested)
            {
                // first check if previous nested item itself is parents or not
                if((currentIndent - prevIndent) >= INDENT_UNIT)
                {
                    // deep nesting starts
                    // trim "</li>" or "</li>" from previous line if previous line itself another nested list item but parents
                    sr.at(lineCounter-1).m_line = 
                    sr.at(lineCounter-1).m_line.substr(0, sr.at(lineCounter -1).m_line.size() - 5);
                    trim = "<ul>" + trim;
                }
                if((currentIndent - nextIndent) >= INDENT_UNIT)
                {
                    // deep nesting ends
                    trim = trim + "</ul></li>";
                    std::cout << "Deep nesting ends!\n";
                }


            }

            if(!isNestedItem(record.future))
            {
                /* 
                    check if current nested item is the last item of nested list   
                    to close that parents list
                */
                trim += "</ul></li>";   

                if(isOlistItem(record.future) && !record.isParentOrdered)
                {
                    // if future plain list item is ordered list item but current item's parent is unordered
                    trim +=  "</ul>";
                }
                else if(isUlistItem(record.future) && record.isParentOrdered)
                {
                    // if future plain list item is unordered list item but current item's parent is ordered
                    trim +=  "</ol>";
                }
            }
        }
        else 
        {
            // plain list items

            if(!record.isParentOrdered)
            {
                // when there was uninterrupted unordered list already , no need to re-initiate 
                trim = trim + "</ul>";
            }
            else 
            {
                trim = "<ul>" + trim + "</ul>";
            }

            if(isNestedItem(record.future))
            {
                // if next list item is nested then keep record of current list status as parent
                record.isParentOrdered = false;
            }
        }
    }

    ld.indentation = countIndentation, ld.listifiedLine = trim;
    return ld;
}

std::string parseList(std::string content)
{
    std::istringstream stream(content);
    std::string previousLine,  line, output = "";
    size_t i = 0;
    lineDescriptor ld;
    listState linestate;
    bool nested;

    while (std::getline(stream, line))
    {
        /* 
            step1: Check if line is ordered or unordered list item or a non-list line
            step2: If line is list item check if it's nested or not
            step3: If nested check indentation level
        */

       record.future = stateDescriptor(stream, linestate);    
       lineCounter++;   
       
        if(isOlistItem(line))
        {
            std::cout << "line? :" << line <<'\n';
            nested = isNestedItem(line);
            ld = listifyLine(line, true);
            ld.itemType = OLISTITEM;
        }
        else if(isUlistItem(line))
        {
            std::cout << "line? :" << line <<'\n';
            nested = isNestedItem(line);
            ld = listifyLine(line, false);
            ld.itemType = ULISTITEM;
        }
        else 
        {
            // In case of non-list items
            ld.indentation = 0;
            ld.listifiedLine = line;
            ld.itemType = NLISTITEM;
            nested = false;
        }
        record.present = ld.listifiedLine;
        record.past = line;
        ld.nested = nested;
        std::cout << "Nested? :" << ld.nested <<'\n';
        std::cout << "Line after parsing: " << record.present << '\n';
        sr.emplace_back(ld.listifiedLine, ld.itemType, ld.nested);
        output += ld.listifiedLine;
    }
    return output;
}

