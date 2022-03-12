#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
每个学生的总成绩都由期末考试成绩（占据40%）、其中考试成绩（占20%）和家庭作业平均成绩（占40%）构成

现在需要增加新的功能,输出家庭作业的中位数或平均数,这需要保存之前输入的数据,使用vector
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
    std::cout << "Enter all your homework grades,"
                 " followed by end-of-file: ";
    
    std::vector<double> homework;
    int count = 0;
    double sum = 0;

    double x;

    //到目前位置,读了count个家庭作业成绩
    while (std::cin >> x) {
        homework.push_back(x);
        ++count;
        sum += x;
    }
    
    //一个良好的习惯,保持系统环境的独立性,不直接编写类型,而是使用size_type表示size
    //为了快速得到该类型,使用typedef表示我们的vec_sz为一个替代名
    typedef std::vector<double>::size_type vec_sz;
    vec_sz size = homework.size();

    if(size == 0) {
        std::cout << std::endl << "You must enter your grades."
                                  "Please try again." << std::endl;
        return 1;//返回1表示失败
    }
    
    //获取中位成绩
    sort(homework.begin(), homework.end());
    vec_sz mid = size / 2;
    double median = size % 2 == 0 ? (homework[mid] + homework[mid - 1]) / 2 : homework[mid];
    

    //输出成绩
    std::streamsize prec = std::cout.precision();
    std::cout << "Your final grade is " << std::setprecision(3)
         << 0.2 * midterm + 0.4 * final + 0.4 * sum / count
         << std::setprecision(prec) << std::endl;

    return 0;
}