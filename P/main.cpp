#include <iostream>
#include <sstream>

int main()
{
    int current_number;
    std::string s;
    std::getline(std::cin, s);
    std::stringstream ss(s);
    while(ss >> current_number)
    {
        std::cout << current_number * current_number * current_number << " ";
    }

    std::cout << std::endl;
    return 0;
}
