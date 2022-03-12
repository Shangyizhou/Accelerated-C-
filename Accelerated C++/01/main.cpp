#include <iostream>
#include <string>
#include <unistd.h>

int main()
{
    std::cout << "Please enter your first name:";
    std::string name;
    std::cin >> name;

    const std::string greeting = "hello, " + name + "!";

    const std::string spaces(greeting.size(), ' ');
    const std::string second = "*" + spaces + "*";

    const std::string first(second.size(), '*');
    
}