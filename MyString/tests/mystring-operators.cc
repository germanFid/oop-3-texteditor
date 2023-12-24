#include <gtest/gtest.h>
#include "../src/mystring.h"
#include "test_tools.h"


TEST(MyString_operators, cstr)
{
    std::string s(gen_random_str(gen_random_num()));
    MyString a(s);

    ASSERT_STREQ(a.c_str(), s.c_str());
}

TEST(MyString_operators, length_size)
{
    std::string s(gen_random_str(gen_random_num()));
    MyString a(s);
    MyString a_double;

    a_double.append(s);
    a_double.append(s);

    ASSERT_EQ(a.length(), s.length());
    ASSERT_EQ(a.size(), s.length());
    ASSERT_EQ(a_double.length(), s.length() * 2);
}

TEST(MyString_operators, empty)
{
    MyString a;
    
    ASSERT_TRUE(a.empty());
}

TEST(MyString_operators, capacity)
{
    std::string s(gen_random_str(gen_random_num()));
    MyString a(s);

    a.erase(0, 1);
    a.erase(1, 1);

    ASSERT_NE(a.length(), s.length());
    ASSERT_EQ(a.length(), s.length() - 2);
    ASSERT_EQ(a.capacity(), s.length());
}

TEST(MyString_operators, shrink_to_fit)
{
    std::string s(gen_random_str(gen_random_num()));
    MyString a(s);

    a.erase(0, 1);
    a.erase(1, 1);
    a.shrink_to_fit();

    ASSERT_EQ(a.capacity(), s.length() - 2);
}

TEST(MyString_operators, clear)
{
    std::string s(gen_random_str(gen_random_num()));
    MyString a(s);

    a.clear();

    ASSERT_TRUE(a.empty());
    ASSERT_EQ(a.length(), 0);
    ASSERT_NE(a.capacity(), 0);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}