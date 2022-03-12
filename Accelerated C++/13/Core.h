#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <vector>
#include <string>
#include "grade.h"
#include "read_hw.h"

class Core
{
public:
    Core() : midterm(0), final(0) { }
    Core(std::istream& is) { read(is); }

    std::string name() const;
    
    virtual std::istream& Core::read(std::istream& in);
    virtual double grade() const;

    virtual ~Core() { }
protected:  
    std::istream& read_common(std::istream& in);
    double midterm, final;
    std::vector<double> homework;

    virtual Core* clone() const { return new Core(*this); }

private:
    std::string n;
    friend class Student_info;
};

/*
继承Core的Grad类
    Core:基类
    Grad:派生类

    Core类的每个成员(构造函数、赋值运算符函数和析构函数除外)也是Grad的成员
*/
class Grad:public Core
{
public:
    Grad() : thesis(0) {}
    Grad(std::istream& is) { read(is); }
    double grade() const;
    std::istream& read(std::istream&);


private:
    double thesis;

    Core* clone() const { return new Grad(*this); }
};


bool compare(const Core&, const Core&);

//我们考虑靠总成绩来排序,我们接收的两个参数可以为Core 或 Grad（转换）
//运行时绑定,如果是Grad则调用Grad::grand()
bool compare_Core_ptrs(const Core& cp1, const Core* cp2);

#endif