cmake_minimum_required(VERSION 3.15)
project(texteditor 
    VERSION 0.1.0 
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXT_LIB MyString/src/charlist.h MyString/src/mystring.h MyString/src/mystring.cpp MyString/src/Aho-Corasick/aho.cpp MyString/src/Aho-Corasick/aho.h)

add_library(mystring STATIC ${EXT_LIB})

add_executable(main src/main.cpp)
