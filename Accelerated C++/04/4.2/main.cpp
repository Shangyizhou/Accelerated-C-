#include <iomanip>
#include <ios>
#include <stdexcept>
#include <algorithm>
#include "student_info.h"
#include "grade.h"

int main()
{
    std::vector<Student_info> students;
    Student_info record;
    std::string::size_type maxlen = 0;
    
    //读并储存所有记录,然后找出最长的姓名长度
    while (read(std::cin, record)) {
        maxlen = std::max(maxlen, record.name.size());
        students.push_back(record);
    }

    //按照姓名字符串长度排序
    std::sort(students.begin(), students.end(), compare);

    //输出每个学生的姓名,并且按照格式对齐
    for (std::vector<Student_info>::size_type i = 0; i != students.size(); i++) {
        std::cout << students[i].name << std::string(maxlen + 1 - students[i].name.size(), ' ');
        //计算输出成绩
        try {
            double final_grade = grade(students[i]);
            std::streamsize prec = std::cout.precision();
            std::cout <<  std::setprecision(3) << final_grade << std::setprecision(prec) << std::endl;
        } catch (std::domain_error error) {
            std::cout << error.what() << std::endl;
        }
        std::cout << std::endl;
    
    }
    return 0;
}