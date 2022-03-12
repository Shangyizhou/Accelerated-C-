#include <iostream>
#include <algorithm>
#include <exception>
#include <ios>
#include <iomanip>
#include "Student.h"

bool compare(const Student& a, const Student& b)
{
    return a.getname() < b.getname();
}

int main()
{
    std::vector<Student> students;
    Student record;
    std::string::size_type maxlen = 0;

    while (record.read(std::cin)) {
        maxlen = std::max(maxlen, record.getname().size());
        students.push_back(record);
    }

    std::sort(students.begin(), students.end(), compare);
    for (std::vector<Student>::iterator iter = students.begin(); iter != students.end(); iter++)
    {
        std::cout << iter->getname() << std::string(maxlen + 1 - iter->getname().size(), ' ');
        try {
            double final_grade = iter->grade();
            std::streamsize prec = std::cout.precision();
            std::cout << std::setprecision(3) << final_grade << std::setprecision(prec) << std::endl;
        } catch (std::domain_error error) {
            std::cout << error.what() << std::endl;
        }
    }

    return 0;
}