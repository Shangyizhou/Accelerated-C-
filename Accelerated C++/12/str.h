#ifndef STR_H
#define STR_H

#include "../11/Vec.h"
#include <iostream>
#include <cstring>
#include <algorithm>

/*
我们需要给Str假如如下操作,使用重载运算符
    cin >> s
    cout << s
    s[i]
    s1 + s2

    对于二元运算符函数
        其左操作数必须作为函数的第一个参数,右操作数必须作为函数的第二个参数
        如果运算符函数是成员函数,那么左操作数总是会默认传递给该成员函数
        cin >> s <=> cin.operator>>(s) >>为istream的一个成员

    那好,如果我们在Str内部实现了重载,那么会是这样子
    s.operator>>(cin) <=> s >> cin

    这与我们的日常调用不符合,所以得到结论:输入和输出函数不能作为类的成员函数

使用友元函数:
     friend std::istream& operator>>(std::istream&, Str&);

重载加号运算符
    一般要重载  + 和 +=, 先实现 +=
    += 实现为成员函数,因为其改变了本身值,相应的只用写一个形参 
        Str& operator+=(const Str& s);
    注意记得返回 *this

    + 实现为全局函数,毕竟只是相加两个字符串,得到一个新的,不涉及改变本身(因为是返回临时变量,所以不能返回引用)
        Str operator+(const Str& a, const Str& b);

参数转换细节
    我们的Str能进行的 + 操作要求两边是Str类型,但是我们给出的是"Hello"这样的const char*类型,但因为Str(const char*),所以会发生参数转换
    Str greeting = "Hello," + name + "!";

    //等价于如下
    Str temp1("Hello,");
    Str temp2 = temp1 + name;
    Str temp3("!");
    Str S = temp2 + temp3;
    
    这会生成许多临时变量,性能不好,所以标准库的string类不会依赖于自动转换实现混合类型的操作数相加
    它会重载许多的 + 号运算符,为每一种可能的操作数类型的连接定义一个版本

设计二元运算符
    如果一个类支持转换,那么将二元运算符定义成非成员函数会好一些,可以保证操作数的对称性
    如果一个运算符函数是类的成员函数,那么这个运算符的左操作数不能是自动转换得到的结果 比如 x + y...
*/

class Str;
std::istream& operator>>(std::istream&, Str&);
std::ostream& operator<<(std::ostream& os, const Str& s);
Str operator+(const Str& a, const Str& b);

class Str
{
public:
    typedef Vec<char>::size_type size_type;
    friend std::istream& operator>>(std::istream&, Str&);

public:
    //此函数可将一个类类型变量转换成double类型变量
    //比如需要double类型变量时候却给了一个Student_info变量,那么编译器就会将它转换成double
    operator double() const;

public:
    //默认构造函数
    Str() {}
    //有参构造函数
    Str(size_type n, char c) : data(n, c) {}
    //将[first, last)范围元素拷贝到data之后
    Str(const char* cp) {
        std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
    }
    
    //重载索引运算符
    char& operator[](size_type i) { return data[i]; }
    const char& operator[](size_type i) const { return data[i]; }

    //重载 += 运算符
    Str& operator+=(const Str& s) {
        std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
        return *this;
    }

    size_type size() const { return data.size(); }
    

private:
    Vec<char> data;
};

//重载输出运算符(进一步调用Vec::operator[])
std::ostream& operator<<(std::ostream& os, const Str& s)
{
    for (Str::size_type i = 0; i != s.size(); i++)
        os << s[i];
    return os;
}

std::istream& operator>>(std::istream& is, Str& s)
{
    //抹去存在的值(s)
    //clead()是data的私有函数,需要靠友元调用
    s.data.clear();

    //按序读字符并忽略前面的空格字符
    char c;
    while (is.get(c) && isspace(c));

    if (is) {
        do {
            s.data.push_back(c);
        } while (is.get(c) && !isspace(c));

        //如果遇到一个空格字符,将它放入输入流的后面
        //ungent函数取消最后一此从输入流中读取一个字符的操作,如果之前读到了空白字符,那么就会取消掉
        if (is)
            is.unget();
    }
    return is;
       
}

Str operator+(const Str& a, const Str& b)
{
    Str tmp = a;
    tmp += b;
    return tmp;
}

#endif