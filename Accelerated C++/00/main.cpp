//iostream表示对输入输出流的支持
#include <iostream>

//返回值告诉编译器程序是否成功运行,0表示成功,其他表示有问题
int main()
{
    
    /*
        1.std::表示这是名为std名称空间的一部分
        2.这是一个表达式,表达式包括操作数和运算符,<<是运算符,std::cout "Hello World" std::endl是操作数
        运算符的效果取决于操作数类型
        运算符<<有两个操作数，我们使用了两个<<运算符和三个操作数,这是因为<<是左结合的
        (std::cout << "Hello World") << std::endl
    */
    std::cout << "Hello World" << std::endl;

    return 0;
}