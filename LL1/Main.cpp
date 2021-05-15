
#include "LL1.cpp"
#include <iostream>

int main()
{
    std::string inputString = "aabbdcc#";
    std::cout << "Adjon meg egy szot! \n";
    std::cin >> inputString;
    LL1 ll1(inputString);
    ll1.analyze();
}
