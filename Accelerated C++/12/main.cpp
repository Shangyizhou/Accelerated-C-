#include "str.h"
#include <string>
int main()
{
    //如果是 explicit Str(const char* cp) { /.../ } 那么则不能隐式构造
    //编译器调用Str(const char*)生成一个临时对象,然后调用自动的赋值运算符,赋值给s s2
    Str s = "hello";
    Str s2 = "hello world";

    //直接构造
    Str s3("hello world");

    std::cout << s << std::endl;
    std::cin >> s;
    std::cout << s << std::endl;
    
    std::string str;
    std::cin >> str;
    std::cout << str << std::endl;

    return 0;
}