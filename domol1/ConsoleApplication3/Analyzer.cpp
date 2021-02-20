#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "TableRow.cpp";
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
class Analyzer
{
private:
    const std::vector<char> specialCharacters = { '{', '}', '(', '*', ')', ':', '=', '<', '>', ' ', 'e', '$' };
    int index;
    std::string input;
    int Position;
    std::vector<TableRow> resultTable;

public:
    Analyzer(std::string input) {
        this->input = input;
        this->index = 0;
        this->Position = 1;
    }

    std::vector<TableRow> analyze() {
     
        do {
          
            //CHECK: Character is a number
            if (isNumber(input.at(index))) {
                Position = 4;
            }
            //CHECK: Character is a letter
            else if (isLetter(input.at(index))) {
                Position = 2;
            }
            //CHECK: Character is a special character
            else if (isSpecialChar(input.at(index))) {
                switch (input.at(index)) {
                case '(': 
                    Position = 8;
                break;
                case '{': 
                    Position = 6;
                 break;
                case ':': 
                    Position = 13;
                 break;
                case '*': 
                    index++;
                break;
                case '}': 
                    index++;

                break;
                case ')': 
                    index++;
                break;
                default: 
                    Position = 15;
                 break;
                }
            }
            switch (Position) {
            case 2: {
                /*
                Read input and build azonosito
                * */
                std::string builder = "";
                while (!isIndexOutOfRange(index) && isLetter(input.at(index))) {
                    builder += input.at(index);
                    index++;
                }
                Position = 3;
                resultTable.push_back(TableRow(std::string("azonosito"), builder));
                break;
            }
            case 4: {
                /*
                Read input and build szam
                * */
                std::string builder = "";
                while (!isIndexOutOfRange(index) && isNumber(input.at(index))) {
                    builder += input.at(index);
                    index++;
                }
                Position = 5;

                resultTable.push_back(TableRow(std::string("szam"), builder));
                break;
            }
            case 6: {
                /*
                Read input and build {} komment
                * */
                std::string builder = "";
                index++;
                while (!isIndexOutOfRange(index) && input.at(index) != '}') {
                    builder += input.at(index);
                    index++;
                }
                Position = 5;
                index++;

                resultTable.push_back(TableRow(std::string("{} komment"), builder));
                if (isIndexOutOfRange(index)) {

                    resultTable.push_back(TableRow(std::string("azonosito"), builder));
                    Position = 21;
                    break;
                }
                break;
            }
            case 8: {
                /*
                Read input and build (**) komment
                * */
                if (!isIndexOutOfRange(index + 1)) {
                    if (input.at(index + 1) == '*') {
                        std::string builder = "";
                        index += 2;
                        while (!isIndexOutOfRange(index)) {
                            if (input.at(index) == '*') {
                                if (!isIndexOutOfRange(index + 1)) {
                                    if (input.at(index + 1) == ')') {

                                        resultTable.push_back(TableRow(std::string("(**)komment"), builder));
                                        Position = 11;
                                        index++;
                                        break;
                                    }
                                }
                            }
                            builder += input.at(index);
                            index++;
                            // If, the input dont have e close tag, we set as azonisito
                            if (isIndexOutOfRange(index)) {
                                resultTable.push_back(TableRow(std::string("azonosito"), builder));
                                Position = 21;
                                Position = 21;
                                break;
                            }
                        }
                    }
                }
                index++;
                break;
            }
            case 13: {
                if (!isIndexOutOfRange(index + 1)) {
                    if (input.at(index + 1) == '=') {

                        resultTable.push_back(TableRow(std::string("ertekadas"), std::string("ertekadas")));
                        Position = 21;
                        index += 2;
                    }
                    else {
                        Position = 21;
                        break;
                    }
                }
                break;
            }
            }

            //CHECK the string end
            if (isIndexOutOfRange(index)) {
                Position = 21;
            }
        } while (Position < 21);




        return this->resultTable;
    }

    void printResult() {
        for (int i = 0; i < resultTable.size(); i++) {
            std::cout << resultTable[i].toString() << std::endl;
        }
    }



 private:
    bool isSpecialChar(char c) {
        for (int i = 0; i < this->specialCharacters.size(); i++) {
            if (specialCharacters[i] == c) {
                return true;
            }
        }
        return false;
    }

    bool isIndexOutOfRange(int index) {
        if (index >= input.length()) {
            return true;
        }
        return false;
    }

    bool isLetter(char letter) {
        for (int c = 'a'; c <= 'z'; c++) {
            if (tolower(letter) == c) {
                return true;
            }
        }
        return false;
    }

    bool isNumber(char letter) {
            if (isdigit(letter)) {
                return true;
            }
       
        return false;
    }

};


