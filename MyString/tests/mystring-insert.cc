#include <gtest/gtest.h>
#include "../src/mystring.h"
#include "test_tools.h"

TEST(MyString_insert, index_count_char)
{
    MyString a;
    int count = gen_random_num();
    a.insert(0, count, 'g');

    ASSERT_EQ(a.length(), count);
    ASSERT_EQ(a[count - 1], 'g');
}

TEST(MyString_insert, index_cstr)
{
    std::string s1(gen_random_str(gen_random_num()));
    MyString a;
    MyString b;
    const char* cstr = s1.c_str();

    a.insert(0, cstr);
    b.insert(0, cstr);
    b.insert(2, cstr);

    ASSERT_EQ(a.length(), s1.length());
    ASSERT_EQ(cstr[0], b[2]);
}

TEST(MyString_insert, index_cstr_count)
{
    std::string s1(gen_random_str(gen_random_num()));
    MyString a;
    MyString b;
    const char* cstr = s1.c_str();

    a.insert(0, cstr, 2);

    ASSERT_EQ(a.length(), s1.length() * 2);
}

TEST(MyString_insert, index_stdstring)
{
    std::string s1(gen_random_str(gen_random_num()));
    MyString a;
    MyString b;

    a.insert(0, s1);
    b.insert(0, s1);
    b.insert(2, s1);

    ASSERT_EQ(a.length(), s1.length());
    ASSERT_EQ(s1[0], b[2]);
}

TEST(MyString_insert, index_stdstring_count)
{
    std::string s1(gen_random_str(gen_random_num()));
    MyString a;
    MyString b;

    a.insert(0, s1, 2);

    ASSERT_EQ(a.length(), s1.length() * 2);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}