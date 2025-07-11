#include <fstream>
#include <iostream>

#include "mdparser.hpp"

int main(int argc, char const *argv[])
{
    MarkdownParser mp;
    std::string filename = "test.html";
    std::string mdcontent = 
    "# Project Overview\n"
    "\n"
    "> *Note*: This doc outlines **v0.1** features.\n"
    "\n"
    "## Goals\n"
    "\n"
    "- **Modularity**\n"
    "  - Components:\n"
    "    - Auth\n"
    "      - Login\n"
    "      - Logout\n"
    "    - UI\n"
    "      - Light mode\n"
    "      - Dark mode\n"
    "        - 🌙 ~Default for devs~\n"
    "- Simplicity\n"
    "  - Avoid over-engineering\n"
    "  - Write *clean*, **maintainable** code\n"
    "\n"
    "## Features\n"
    "\n"
    "1. User System\n"
    "   - Sign up\n"
    "   - Email verification(moved to v0.2)\n"
    "   - Password reset\n"
    "2. Dashboard\n"
    "   - Stats\n"
    "     - Active users\n"
    "     - Engagement\n"
    "   - ==Notifications==\n"
    "\n"
    "## Dev Notes\n"
    "\n"
    "> \"_Move fast, but don't break things._\"\n"
    "\n"
    "- Write tests\n"
    "   - Unit\n"
    "   - Integration\n"
    "- Respect deadlines\n"
    "- Use spaces, not tabs 😅\n";

    
    std::ofstream file(filename);
    file << mp.parse(mdcontent);
    file.close();

    // Open the markdown file with the default viewer
   // int result = std::system("xdg-open test.md");

    std::cout << "HTML output written to " + filename + '\n';

    std::string commad = "xdg-open " + filename;
    const char* launchCode =  commad.c_str(); 
    std::system(launchCode);


    return 0;
}
