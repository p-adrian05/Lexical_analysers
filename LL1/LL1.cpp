

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
class LL1
{

private:
    std::string input = "";
    int indexOfInput = -1;
    std::vector<std::vector<std::string>> table = {
        {"aS", "bAc", "error", "error"},
        {"error", "bAc", "error", "d"}};
    std::vector<std::string> nonTerminals = {"S", "A"};
    std::vector<std::string> terminals = {"a", "b", "c", "d"};

    std::stack<std::string> stack;

public:
    LL1(std::string input)
    {
        this->input = input;
    }

    void push(std::string s)
    {
        this->stack.push(s);
    }

    std::string pop()
    {
        std::string r = this->stack.top();
        this->stack.pop();
        return r;
    }
    std::string read()
    {
        indexOfInput++;
        char ch = this->input.at(indexOfInput);
        std::string str = std::string(1, ch);
        return str;
    }

    int getNonTerminalIndex(std::string s)
    {
        for (int i = 0; i < this->nonTerminals.size(); i++)
        {
            if (s.compare(this->nonTerminals[i]) == 0)
            {
                return i;
            }
        }
        return -1;
    }

    int getTerminalIndex(std::string s)
    {
        for (int i = 0; i < this->terminals.size(); i++)
        {
            if (s.compare(this->terminals[i]) == 0)
            {
                return i;
            }
        }
        return -1;
    }
    std::string getRule(std::string nonTerminal, std::string terminal)
    {

        int row = getNonTerminalIndex(nonTerminal);
        int column = getTerminalIndex(terminal);
        std::string rule = this->table[row][column];
        if (rule.compare("error") == 0)
        {
            std::cout << "error";
        }
        return rule;
    }

    bool isTerminal(std::string s)
    {
        for (int i = 0; i < this->terminals.size(); i++)
        {
            if (s.compare(this->terminals[i]) == 0)
            {
                return true;
            }
        }
        return false;
    }

    bool isNonTerminal(std::string s)
    {
        for (int i = 0; i < this->nonTerminals.size(); i++)
        {
            if (s.compare(this->nonTerminals[i]) == 0)
            {
                return true;
            }
        }
        return false;
    }
    void pushRule(std::string rule)
    {
        for (int i = rule.length() - 1; i >= 0; i--)
        {
            char ch = rule.at(i);
            std::string str = std::string(1, ch);
            push(str);
        }
    }

    void analyze()
    {

        push(this->input.at(0) + "");
        push(this->nonTerminals[0]);
        std::string token = read();
        std::string top;

        do
        {
            top = this->pop();

            if (isNonTerminal(top))
            {
                std::string rule = this->getRule(top, token);
                this->pushRule(rule);
            }
            else if (isTerminal(top))
            {
                if (top.compare(token) != 0)
                {
                    std::string message = "Token nem megfelelo";
                    message.append(token);
                    std::cout << message;
                }
                else
                {
                    token = read();
                }
            }
            else
            {
                break;
            }
            if (token.compare("#") == 0)
            {
                break;
            }

        } while (true);

        if (token.compare("#") == 0)
        {
            std::cout << "Input elfogadva";
        }
        else
        {
            std::cout << "Input elutasitva";
        }
    }
};
