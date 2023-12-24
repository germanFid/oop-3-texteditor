#include <gtest/gtest.h>
#include "../src/mystring.h"
#include "test_tools.h"


TEST(MyString_substr, index)
{
    std::string s1(gen_random_str(gen_random_num()));
    std::string sub_s1;
    MyString a(s1);

    MyString sub_a(a.substr(1));
    sub_s1 = s1.substr(1);

    ASSERT_EQ(sub_a[0], sub_s1[0]);
    ASSERT_EQ(sub_a[sub_a.length() - 1], sub_s1[sub_s1.length() - 1]);
}

TEST(MyString_substr, index_count)
{
    std::string s1(gen_random_str(gen_random_num()));
    std::string sub_s1;
    MyString a(s1);

    MyString sub_a(a.substr(1, 2));
    sub_s1 = s1.substr(1, 2);

    ASSERT_EQ(sub_a[0], sub_s1[0]);
    ASSERT_EQ(sub_a[1], sub_s1[1]);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}