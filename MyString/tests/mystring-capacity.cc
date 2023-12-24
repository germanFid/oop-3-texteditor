#include <gtest/gtest.h>
#include "../src/mystring.h"
#include "test_tools.h"

TEST(MyString_erase, erase_index_count)
{
    int len = 5;
    MyString a(gen_random_str(len));
    int start_capacity = a.capacity();


    a.clear();

    ASSERT_EQ(a.capacity(), start_capacity);
    a.append("b");
    a.append("c");
    ASSERT_EQ(a.capacity(), start_capacity);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}