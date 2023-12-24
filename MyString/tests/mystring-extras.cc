#include <gtest/gtest.h>
#include "../src/mystring.h"
#include "test_tools.h"

TEST(MyString_extras, int_conversion)
{
    MyString a("1123312312");
    
    long n = a.to_long();

    ASSERT_EQ(1123312312, n);
}

TEST(MyString_extras, float_conversion)
{
    MyString a("15.14");
    
    float f = a.to_float();

    ASSERT_EQ(15.14f, f);
}

TEST(MyString_extras, double_conversion)
{
    MyString a("15.14");
    
    double f = a.to_double();

    ASSERT_EQ(15.14, f);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
