cmake_minimum_required(VERSION 3.10)
project(parser)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)

add_executable(mdparser 
          tests/main.cpp
          src/bold.cpp 
          src/boldnitalic.cpp
          src/code.cpp
          src/header.cpp 
          src/highlight.cpp
          src/hrule.cpp
          src/image.cpp
          src/italic.cpp
          src/link.cpp
          src/list.cpp 
          src/quote.cpp 
          src/strikethrough.cpp
          src/mdparser.cpp)