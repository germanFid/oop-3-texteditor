#include <gtest/gtest.h>
#include "../src/mystring.h"
#include "test_tools.h"

TEST(MyString_erase, erase_index_count)
{
    int len = gen_random_num();
    MyString a(gen_random_str(len));

    a.erase(0, 1);
    a.erase(1, 1);

    ASSERT_EQ(len - 2, a.length());
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
