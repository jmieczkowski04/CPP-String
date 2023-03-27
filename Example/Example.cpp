#include <iostream>
#include <CString.h>



int main()
{
    CString str("www");
    str = "http";
    str = str + "s";
    str += "://";

    CString str2("example");
    CString str3 = ".com";

    str2 = str2 + str3;
    str += str2;

    std::cout << *str << " " << str[2] << str[3] << " " << str.GetSize();
}
