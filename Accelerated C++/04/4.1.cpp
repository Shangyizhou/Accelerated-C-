#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

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
}

/*
函数重载

*/
double grade(double midterm, double final, const std::vector<double>& hw)
{
    if (hw.size() == 0)
        throw std::domain_error("student has done no homework");
    return grade(midterm, final, median(hw));
}

/*
    1.读写家庭作业(返回两个值：读到的家庭作业; 输入是否成功)
    2.hw不用const说明我们需要改变它的值
    3.注意我们返回的是引用
*/
std::istream& read_hw(std::istream& in, std::vector<double>& hw)
{
    //我们不了解cin,但可以理解为一种数据结构,那么我们输入的信息都被存放在这个数据结构中,并且可以确定cin会收到改变
    if (in) {
        //清除原来的内容
        hw.clear();

        //读家庭作业
        double x;
        while (in >> x) {
            hw.push_back(x);
            //清除流以使下一个动作有效(如果出错也会被清除,不影响下一次读取)
            in.clear();
        }
    }

    return in;
}


int main()
{
    std::cout << "Please enter your first name:";
    std::string name;
    std::cin >> name;
    std::cout << "Hello" << name << "!" << std::endl;

    std::cout << "Please enter your midterm and final exam grades: ";
    double midterm, final;
    std::cin >> midterm >> final;

    std::cout << "Enter all your homework grades, "
                 "followed by end-of-file:";
    
    std::vector<double> homework;
    read_hw(std::cin, homework);

    //如果 try{} 这些语句中的任何地方发生了一个domain_error异常，那么它就会停止执行这些语句,然后去执行catch() {} 内的语句
    try {
        double final_grade = grade(midterm, final, homework);
        std::streamsize prec = std::cout.precision();
        std::cout << "Your final grade is " << std::setprecision(3) << final_grade << std::setprecision(prec) << std::endl;
    } catch (std::domain_error) { //如果捕获到异常
        std::cout << std::endl << "You must enter your grades."
        "Please try again." << std::endl;
        return 1;
    }

    return 0;
}