
#include "CYK.cpp"
#include <string>
#include <fstream>
#include <iostream>
std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}
int main()
{
    std::vector<std::vector<std::string>> grammer;
    std::ifstream infile;
    std::string line;
    infile.open("grammer.txt");

    if (infile.is_open())
    {
        while (std::getline(infile, line))
        {
            std::vector<std::string> v;
            v.push_back(std::string(1, line.at(0)));
            std::vector<std::string> temp = split(line.substr(2), "|");
            for (int i = 0; i < temp.size(); i++)
            {
                v.push_back(temp[i]);
            }

            grammer.push_back(v);
        }
        infile.close();
    }
    std::string inputString = "aabbaba";
    std::cout << "Adjon meg egy szot! \n";
    std::cin >> inputString;

    CYK cyk(grammer);
    if (cyk.analyze(inputString))
    {
        std::cout << "benne van a " + inputString + " a nyelvben";
    }
    else
    {
        std::cout << " nincs benne a " + inputString + " a nyelvben";
    }
    std::cout << "\n";
}
