#include "student_info.h"

//sort函数
bool compare(const Student_info& a, const Student_info& b)
{
    return a.name < b.name;
}

//读取家庭作业成绩
std::istream& read_hw(std::istream& in, std::vector<double>& hw)
{
    //我们不了解cin,但可以理解为一种数据结构,那么我们输入的信息都被存放在这个数据结构中,并且可以确定cin会收到改变
    if (in) {
        //清除原来的内容,否则公用一个record,前面一个未清除,后面一个则继承它的值
        hw.clear();

        //读家庭作业
        double x;
        std::cout << "Please enter the homework" << std::endl;
        while (in >> x) {
            hw.push_back(x);
        }
        //清除流以使下一个动作有效(如果出错也会被清除,不影响下一次读取)
        //我们使用CTRL + D结束输入,会返回一个错误值,需要清除此错误值
        in.clear();
    }

    return in;
}

std::istream& read(std::istream& in, Student_info& s)
{
    std::cout << "Please enter your name, your midtern and your final" << std::endl;
    in >> s.name >> s.midterm >> s.final;

    //读取家庭作业成绩
    read_hw(in, s.homework);

    return in;
}













