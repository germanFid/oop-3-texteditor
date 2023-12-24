#include <gtest/gtest.h>
#include "../src/mystring.h"
#include "test_tools.h"

#define TEST_LEN 30

TEST(MyString_find, cstr)
{
    std::string s1(gen_random_str(TEST_LEN));
    int substr_start = gen_random_num();
    int substr_len = gen_random_num();
    MyString a(s1);
    
    std::string sub = s1.substr(substr_start, substr_len);
    const char* cstr = sub.c_str();

    int result = a.find(cstr);

    ASSERT_EQ(result, s1.find(sub, 0));
}

TEST(MyString_find, cstr_index)
{
    std::string s1(gen_random_str(TEST_LEN));
    int substr_start = gen_random_num();
    int substr_len = gen_random_num();
    MyString a(s1);
    
    std::string sub = s1.substr(substr_start, substr_len);
    const char* cstr = sub.c_str();

    int result = a.find(cstr, substr_start - 1);

    ASSERT_EQ(result, s1.find(sub, substr_start - 1));
}

TEST(MyString_find, stdstring)
{
    std::string s1(gen_random_str(TEST_LEN));
    int substr_start = gen_random_num();
    int substr_len = gen_random_num();
    MyString a(s1);
    
    std::string sub = s1.substr(substr_start, substr_len);

    int result = a.find(sub);

    ASSERT_EQ(result, s1.find(sub, 0));
}

TEST(MyString_find, stdstring_index)
{
    std::string s1(gen_random_str(TEST_LEN));
    int substr_start = gen_random_num();
    int substr_len = gen_random_num();
    MyString a(s1);
    
    std::string sub = s1.substr(substr_start, substr_len);

    int result = a.find(sub, substr_start - 1);

    ASSERT_EQ(result, s1.find(sub, substr_start - 1));
}

TEST(MyString_find, trie_find)
{
    MyString a("hello, world! What an amazing day. Big brown fox jumps over the lazy dog today. man...");
    
    std::vector<char*> substrs;
    substrs.push_back("meow");
    substrs.push_back("day");
    substrs.push_back("an");

    std::unordered_multimap<char*, int> results = a.trie_find(substrs, 0);

    int day = 0;
    int meow = 0;
    int an = 0;

    for (auto& it: results)
    {
        if (!strcmp ("day", it.first))
        {
            day++;
            continue;
        }

        if (!strcmp("meow", it.first))
        {
            meow++;
            continue;
        }

        if (!strcmp ("an", it.first))
        {
            an++;
            continue;
        }
    }

    ASSERT_EQ(meow, 0);
    ASSERT_EQ(day, 2);
    ASSERT_EQ(an, 2);
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}