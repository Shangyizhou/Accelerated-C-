#include <iostream>
#include "Vec.h"

int main()
{
    Vec<int> v;
    Vec<int> v2(2, 20);
    Vec<int> v3(v2);
    v3 = v2;
    v2.push_back(2);
    v2.push_back(20);
    v2.push_back(30);
    Vec<int>::const_iterator it = v2.begin();
    while (it != v2.end()) {
        std::cout << *it << std::endl;
        it++;
    }
    std::cout << v2.size() << std::endl;

    return 0;
}