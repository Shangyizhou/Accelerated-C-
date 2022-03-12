#ifndef GRADE_H
#define GRADE_H

#include <vector>
#include <algorithm>
#include "student_info.h"

double grade(double, double, double);
double grade(double, double, const std::vector<double>&);
double grade(const Student_info&);
double median(std::vector<double>);

#endif