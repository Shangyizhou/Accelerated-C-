#include "Core.h"

std::string Core::name() const
{
    return n;
}

double Core::grade() const
{
    //调用全局作用域的grade(进一步调用median处理homework的中位数;再最后调用计算加权的grade)
    return ::grade(midterm, final, homework);
}

std::istream& Core::read_common(std::istream& in)
{
    in >> n >> midterm >> final;
    return in;
}

std::istream& Core::read(std::istream& in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}

/**********************************************
**************   Grad   **********************
**********************************************/
std::istream& Grad::read(std::istream& in)
{
    read_common(in);
    in >> thesis;
    read_hw(in, homework);
    return in;
}

bool compare(const Core& c1, const Core& c2)
{
	return c1.name() < c2.name();
}

bool compare_Core_ptrs(const Core* cp1, const Core* cp2)
{
	return compare(*cp1, *cp2);
}
