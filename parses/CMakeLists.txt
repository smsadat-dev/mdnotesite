cmake_minimum_required(VERSION 3.10)
project(parser)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)

add_executable(mdparser 
          main.cpp 
          src/bold.cpp 
          src/boldnitalic.cpp
          src/callouts.cpp
          src/code.cpp
          src/definitionlist.cpp
          src/emojis.cpp
          src/escape.cpp
          src/footnote.cpp
          src/header.cpp 
          src/highlight.cpp
          src/hrule.cpp
          src/htmlblk.cpp
          src/image.cpp
          src/italic.cpp
          src/link.cpp
          src/list.cpp 
          src/mathsyntx.cpp
          src/quote.cpp 
          src/strikethrough.cpp
          src/table.cpp
          src/tasklist.cpp
          src/toc.cpp
          src/mdparser.cpp)