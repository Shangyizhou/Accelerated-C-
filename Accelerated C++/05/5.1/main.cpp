#include <iostream>
#include <vector>
#include <list>
#include <exception>
#include "grade.h"
#include "student_info.h"
/*
希望抽取出课程不过关的学生的记录,将这些记录保存到另一个数组中
*/

//判断学生是否不合格
bool fgrade(const Student_info& s)
{
    return grade(s) < 60;
}

/*
//遍历学生数组,将合格的放入pass数组,不合格的放入fail数组(缺陷:需要副本，浪费空间)
std::vector<Student_info> extract_fails(std::vector<Student_info>& students)
{
    std::vector<Student_info> pass, fail;
    for (std::vector<Student_info>::size_type i = 0; i < students.size(); i++) {
        if (fgrade(students[i]))
            fail.push_back(students[i]);
        else 
            pass.push_back(students[i]);
    }
    students = pass;
    return fail;
}
*/

/*
//此种方法直接就地删除,删除元素需要耗费大量时间,如果数据规模较大,这样子会降低不少性能
std::vector<Student_info> extract_fails(std::vector<Student_info>& students) 
{
    std::vector<Student_info> fail;
    std::vector<Student_info>::size_type i = 0;

    //因为我们会删除元素,所以students.size()会一直改变,不能使用原来的size,需动态获得当前size
    while (i != students.size()) {
        if (fgrade(students[i])) {
            fail.push_back(students[i]);
            //students.begin()表示索引为0的元素,将它与索引 i 相加,即为索引为i的那个元素
            //erase会调整索引,调整后的索引会指向下一个元素,所以它不用再继续 i++ 了
            students.erase(students.begin() + i); 
        } else {
            i++;
        }
    }
}
*/

//迭代器版本
std::vector<Student_info> extract_fails(std::vector<Student_info>& students)
{
    std::vector<Student_info> fail;
    for (std::vector<Student_info>::iterator it = students.begin(); it != students.end(); it++) 
    {
        if (fgrade(*it)) {
            fail.push_back(*it);
            //删除之后,该迭代器指向的元素被删除了,该迭代器失效了(其后面的元素也无法通过it获得),
            //但是erase返回一个迭代器,这个迭代器紧跟在删除元素的下一个元素
            it = students.erase(it); 
        } 
    }
    return fail;
}

/*
用list代替vector
    跟vector不同,list是双向链表,不是连续排序的,所以删除某元素不会导致指向后面元素的迭代器失效
    而vector删除元素,后面元素会往前移动,导致迭代器失效
*/
std::list<Student_info> extract_fails(std::list<Student_info>& students)
{
    std::list<Student_info> fail;
    std::list<Student_info>::iterator iter = students.begin();
    while (iter != students.end()) {
        if (fgrade(*iter)) {
            fail.push_back(*iter);
            //同样,删除了该元素,该迭代器就失去了作用(后面的迭代器没事),也无法通过 iter++ 获得下一个迭代器,所以需要重新赋值
            iter = students.erase(iter);
        } else {
            iter++;
        }
    }
}
