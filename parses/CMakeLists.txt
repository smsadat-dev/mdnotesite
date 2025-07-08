cmake_minimum_required(VERSION 3.10)
project(parser)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)

add_executable(mdparser 
          main.cpp 
          src/bold.cpp 
          src/boldnitalic.cpp
          src/code.cpp
          src/emojis.cpp
          src/escape.cpp
          src/header.cpp 
          src/hrule.cpp
          src/image.cpp
          src/italic.cpp
          src/linebreak.cpp
          src/link.cpp
          src/olist.cpp 
          src/quote.cpp 
          src/ulist.cpp
          src/mdparser.cpp)