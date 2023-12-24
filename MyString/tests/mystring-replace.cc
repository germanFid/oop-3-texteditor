#include <gtest/gtest.h>
#include "../src/mystring.h"
#include "test_tools.h"


TEST(MyString_replace, index_count_cstr)
{
    std::string s1(gen_random_str(gen_random_num()));
    std::string s2(gen_random_str(gen_random_num()));
    MyString a(s1);
    const char* cstr = s2.c_str();

    a.replace(0, 2, cstr);

    ASSERT_EQ(s2[0], a[0]);
    ASSERT_EQ(s1[2], a[s2.length()]);
}

TEST(MyString_replace, index_count_string)
{
    std::string s1(gen_random_str(gen_random_num()));
    std::string s2(gen_random_str(gen_random_num()));
    MyString a(s1);

    a.replace(0, 2, s2);

    ASSERT_EQ(s2[0], a[0]);
    ASSERT_EQ(s1[2], a[s2.length()]);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}