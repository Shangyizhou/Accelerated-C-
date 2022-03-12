#include "median.h"

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