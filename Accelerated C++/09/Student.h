#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>


/*
对之前的数据结构进行封装,封装成Student类
*/
class Student
{
public:
    Student() : midterm(0), final(0), name("") {}
    Student(std::istream& is) { //读一个流从而创建对象
        read(is);
    }

public:

public:
    std::istream& read(std::istream&);
    double grade() const;
    
    //函数名是name时,返回name会报错,编译器误认为是转换成什么形式
    //const保证我们不能在获取这个名字时改变成员变量
    //compare会被设计成类外函数,那么直接访问成员变量也会破坏封装性,所以用此函数获取某成员变量就很好
    bool valid() const {
        return !homework.empty();
    }
    std::string getname() const {
        return name;
    }

public:
    double grade(double, double, double);
    double grade(double, double, const std::vector<double>&);
    double grade(const Student&);
    double median(std::vector<double>);

private:
    std::string name;
    double midterm, final;
    std::vector<double> homework;
};



#endif