#include <iostream>
#include <vector>
#include <string>
#include <cctype>

std::vector<std::string> my_split(const std::string& s)
{
    std::vector<std::string> res;
    typedef std::string::size_type string_size;
    string_size i = 0;
    
    while (i != s.size()) {
        //越过空白字符,当是空白字符时继续前进
        while (i != s.size() && isspace(s[i])) {
            i++;
        }

        //越过字符,当不是空白字符时会继续前进
        string_size j = i;
        while (j != s.size() && !isspace(s[j])) {
            j++;
        }

        //substr(i, n) 剪切出从i开始的n个字符
        if (i != j) {
            res.push_back(s.substr(i, j - i + 1));
            i = j;
        }
    }
    return res;
}

int main()
{
    std::string str;
    //getline(istream, s) 将一个流的数据读到s中 回车结束
    while (getline(std::cin, str)) {
        std::vector<std::string> v = my_split(str);
        for (const auto& elem : v) 
            std::cout << elem << std::endl;
    }


    return 0;
}