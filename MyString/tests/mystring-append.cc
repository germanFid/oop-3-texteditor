#include <gtest/gtest.h>
#include "../src/mystring.h"
#include "test_tools.h"

TEST(MyString_append, count_char)
{
    MyString a;
    int count = gen_random_num();
    a.append(count, 'g');

    ASSERT_EQ(a.length(), count);
    ASSERT_EQ(a[count - 1], 'g');
}

TEST(MyString_append, cstr)
{
    std::string s1(gen_random_str(gen_random_num()));
    MyString a;
    const char* cstr = s1.c_str();

    a.append(cstr);

    ASSERT_EQ(a.length(), s1.length());
}

TEST(MyString_append, cstr_count)
{
    std::string s1(gen_random_str(gen_random_num()));
    MyString a;
    const char* cstr = s1.c_str();

    a.append(cstr, 2);

    ASSERT_EQ(a.length(), s1.length() * 2);
}

TEST(MyString_append, stdstring)
{
    std::string s1(gen_random_str(gen_random_num()));
    MyString a;

    a.insert(0, s1);

    ASSERT_EQ(a.length(), s1.length());
}

TEST(MyString_append, stdstring_count)
{
    std::string s1(gen_random_str(gen_random_num()));
    MyString a;

    a.append(s1, 2);

    ASSERT_EQ(a.length(), s1.length() * 2);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}