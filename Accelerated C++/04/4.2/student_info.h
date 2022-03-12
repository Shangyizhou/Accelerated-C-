//防止文件重复包含
#ifndef STUDENT_INFO_H
#define STUDENT_INFO_H

#include <iostream>
#include <string>
#include <vector>

/*
需要列出一整个班的学生的信息
    将学生的信息整合成结构体,且里面有相应的处理函数
    我们不应该在头文件使用using声明,否则其他包含头文件的都只能使用该作用域下的函数,限制了灵活性
*/
struct Student_info {
    std::string name;
    double midterm, final;
    std::vector<double> homework;
};

bool compare(const Student_info& a, const Student_info& b);
std::istream& read(std::istream& in, Student_info& s);
std::istream& read_hw(std::istream& in, std::vector<double>& hw);

#endif
