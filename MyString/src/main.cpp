#include <iostream>
#include "mystring.h"

int main()
{
    std::string test("Bruh..");
    MyString str = MyString(test);

    std::cout << "Done!\n";
    return 0;
}