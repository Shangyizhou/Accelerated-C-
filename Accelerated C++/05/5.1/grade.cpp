#include "grade.h"

double grade(double midterm, double final, double median)
{
  return 0.2 * midterm + 0.4 * final + 0.4 * median;
}

//重载函数,判断是否数据为空,为空则抛出异常,不空则调用重载函数 grade 和 median 计算
double grade(double midterm, double final, const std::vector<double>& hw)
{
    if (hw.size() == 0)
        throw std::domain_error("student has done no homework");
    return grade(midterm, final, median(hw));
}

//对一个Student_info类型的对象进行处理,返回一个表示总成绩的double类型值
double grade(const Student_info& s)
{
    return grade(s.midterm, s.final, s.homework);
}

//计算中位数
double median(std::vector<double> vec)
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