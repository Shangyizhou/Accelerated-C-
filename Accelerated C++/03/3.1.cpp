#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

/*
每个学生的总成绩都由期末考试成绩（占据40%）、其中考试成绩（占20%）和家庭作业平均成绩（占40%）构成
*/
int main()
{
    //提示
    std::cout << "Please enter your first name:";

    //输入名字
    std::string name;
    std::cin >> name;
    std::cout << "Hello, " << name << "!" << std::endl;

    //输入期中和期末成绩
    std::cout << "Please enter your midterm and final exam grades: ";
    double midterm, final;
    std::cin >> midterm >> final;

    //请求输入家庭作业成绩
    //std::cout << "Enter all your homework grades, followed by end-of-file: ";
    //两个以上的字符串字面量被空白符分割,相当于连在一起
    std::cout << "Enter all your homework grades,"
                 " followed by end-of-file: ";
    
    int count = 0;
    double sum = 0;

    double x;

    //到目前位置,读了count个家庭作业成绩
    //主要我们的输入成功,就会一直输入下去
    //ctrl + D 结束输入
    while (std::cin >> x) {
        ++count;
        sum += x;
    }
    
    //我们需要输出三位有效的总成绩,所以使用setprecision,该控制器为流的后继输出设置了一个特定的有效位
    //返回原先的精度
    std::streamsize prec = std::cout.precision();
    //控制精度为3位,之后又需要将精度调回原样
    std::cout << "Your final grade is " << std::setprecision(3)
         << 0.2 * midterm + 0.4 * final + 0.4 * sum / count
         << std::setprecision(prec) << std::endl;

    return 0;
}