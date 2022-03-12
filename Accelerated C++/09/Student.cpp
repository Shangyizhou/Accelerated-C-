#include "Student.h"

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

std::istream& Student::read(std::istream& in)
{
    in >> name >> midterm >> final;
    read_hw(in, homework);
    return in;
}

double Student::grade(double midterm, double final, double median)
{
  return 0.2 * midterm + 0.4 * final + 0.4 * median;
}


//重载函数,判断是否数据为空,为空则抛出异常,不空则调用重载函数 grade 和 median 计算
double Student::grade(double midterm, double final, const std::vector<double>& hw)
{
    if (hw.size() == 0)
        throw std::domain_error("student has done no homework");
    return grade(midterm, final, median(hw));
}

double Student::grade() const
{
    //::表明我们不想调用该类作用域下的grade函数
    return grade(midterm, final, homework);
}

//计算中位数
double Student::median(std::vector<double> vec)
{
    typedef std::vector<double>::size_type vec_sz;

    vec_sz size = vec.size();
    /*
    抛出异常,如果程序抛出异常,那么它就会在抛出异常的地方终止程序并转移到程序的另一部分,并向这部分提供一个异常对象异常对象中含有调用程序,用来处理异常信息
    domain_error:报告函数参数的取值是函数所不能接受的,可以给出字符串描述出错情况
    */
    if (size == 0) {
        throw std::domain_error("median of an empty vector");
    }
    //排序
    std::sort(vec.begin(), vec.end());
    vec_sz mid = vec.size() / 2;

    //返回中位数
    return vec.size() % 2 == 0 ? (vec[mid-1] + vec[mid]) / 2
    : vec[mid];
}