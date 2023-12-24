#ifndef MYSTRING_H
#define MYSTRING_H

#include <initializer_list>
#include <climits>

#include <iostream>
#include <stdexcept>

#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <vector>
#include <unordered_map>
#include <string> // for std::string constructor


#include "charlist.h"

class InvalidConversionException : public std::exception {
    public:
const char * what () {
        return "Invalid Conversion exception";
    }
};

class MyString
{
private:
    CharList charList;

    void init_from_cstr(const char*);

public:
    MyString(): charList() {};
    MyString(char* cstr);
    MyString(std::string);
    MyString(char*, int);
    MyString(int, char);
    MyString(const MyString&);

    MyString(long long x);
    explicit MyString(int x):MyString((long long)x) {};
    explicit MyString(short x):MyString((long long)x) {};
    explicit MyString(char x):MyString((long long)x) {};


    MyString(float);
    MyString(double);

    // move semantics

    MyString(MyString&&) noexcept;
    MyString& operator=(MyString&& s) noexcept;

    ~MyString();

    // OPERATOR SECTION

    friend std::ostream& operator<<(std::ostream& out, const MyString& s);
    friend std::istream& operator>>(std::istream& in, MyString& s);

    char operator[](int) const;
    MyString operator+(MyString const);
    MyString operator+(char*);
    MyString operator+(std::string);

    MyString& operator+=(char*);
    MyString& operator+=(std::string);

    MyString& operator=(char*);
    MyString& operator=(std::string);
    MyString& operator=(char);

    bool operator>(MyString);
    bool operator<(MyString);
    bool operator>=(MyString);
    bool operator<=(MyString);
    bool operator==(MyString);
    bool operator!=(MyString);

    // 'UTILS' SECTION

    char* c_str() const;
    char* data() const;

    int length() const; // same as size
    int size() const; // return the number of char elements in string

    bool empty() const; // true if empty
    int capacity() const; // number of allocated nodes

    void shrink_to_fit();
    void clear();

    // INSERT section

    void insert(int, int, char);
    void insert(int index, char* cstr);
    void insert(int index, char* cstr, int count);
    void insert(int index, std::string str);
    void insert(int index, std::string str, int count);

    // ERASE SECTION

    void erase(int index, int count);

    // APPEND SECTION

    void append (int count, char c);
    void append (char* cstr);
    void append (char* cstr, int count);
    void append (std::string str);
    void append (std::string str, int count);

    // REPLACE

    void replace(int index, int count, char* cstr);
    void replace(int index, int count, std::string str);

    // SUBSTR

    MyString substr(int index) const;
    MyString substr(int index, int count) const;

    // FIND

    int find(const char* cstr) const;
    int find(const char* cstr, int index) const; // search starts with index position
    int find(std::string str) const;
    int find(std::string str, int index) const; // search starts with index position
    std::unordered_multimap<char*, int> trie_find(
                std::vector<char*>& strings, 
                int index);

    // ADDITIONAL (Task 4)

    short to_short() const;
    char to_char() const;
    int to_int() const;
    long to_long() const;
    float to_float() const;
    double to_double() const;

    char at(int) const;
};

#endif // LINKEDLIST_H