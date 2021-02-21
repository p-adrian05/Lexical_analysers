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
#include <functional>
using namespace std;

class Analyzer
{
private:
    const std::vector<char> specialCharacters = { '{', '}', '(', '*', ')', ':', '=', '<', '>' };
    std::vector<TableRow> resultTable;

public:
    Analyzer() {
        initState();
    }

   

    void analyze(const std::string& input) {
        initState();
        int statePosition = 1;
        int index = 0;
        do {
            if (isIndexOutOfRange(index, input)) {
                statePosition = 21;
            }
            else if (statePosition==1) {
                
                 statePosition = calculcateStatePosition(input.at(index));
            }
           
            
            switch (statePosition) {
            case 2: {
                /*
                Read input and build azonosito
                * */
                std::string lexema = "";
                while (!isIndexOutOfRange(index,input) && isLetter(input.at(index))) {
                    lexema += input.at(index);
                    index++;
                }
                statePosition = 1;
                resultTable.push_back(TableRow(std::string("azonosito"), lexema));
                break;
            }
            case 4: {
                /*
                Read input and build szam
                * */
                std::string lexema = "";
                while (!isIndexOutOfRange(index,input) && isdigit(input.at(index))) {
                    lexema += input.at(index);
                    index++;
                }
                statePosition = 1;

                resultTable.push_back(TableRow(std::string("szam"), lexema));
                break;
            }
            case 6: {
                /*
                Read input and build {} komment
                * */
                std::string lexema = "";
                index++;
                while (!isIndexOutOfRange(index, input) && input.at(index) != '}') {
                    lexema += input.at(index);
                    index++;
                }
                statePosition = 1;
                index++;

                resultTable.push_back(TableRow(std::string("{} komment"), lexema));
                break;
            }
            case 8: {
                /*
                Read input and build (**) komment
                * */
               
                if (!isIndexOutOfRange(index + 1, input)) {
                    if (input.at(index + 1) == '*') {
                        std::string lexema = "";
                        index += 2;
                        while (!isIndexOutOfRange(index, input)) {
                            if (input.at(index) == '*') {
                                if (!isIndexOutOfRange(index + 1, input)) {
                                    if (input.at(index + 1) == ')') {

                                        resultTable.push_back(TableRow(std::string("(**)komment"), lexema));
                                        statePosition = 1;
                                        index++;
                                        break;
                                    }
                                }
                            }
                            lexema += input.at(index);
                            index++;
                           
                        }
                    }
                }
                index++;
                break;
            }
            case 13: {
            
                if (!isIndexOutOfRange(index + 1, input)) {
                    if (input.at(index + 1) == '=') {

                        resultTable.push_back(TableRow(std::string("ertekadas"), std::string("=")));
                        statePosition = 1;
                        index += 2;
                    }
                    else {
                        statePosition = 19;
                     
                    }
                }
                else {
                    statePosition = 19;
                }

                break;
            }
            case 15: {
                if (!isIndexOutOfRange(index + 1, input)) {
                    if (input.at(index + 1) == '=') {
                        resultTable.push_back(TableRow(std::string("kisebbegyenlo"), std::string("<=")));
                        statePosition = 1;
                        index += 2;
                    }
                    else if (input.at(index+1) == '>') {
                        resultTable.push_back(TableRow(std::string("nemegyenlo"), std::string("<>")));
                        statePosition = 1;
                        index += 2;
                    }
                    else if (isdigit(input.at(index + 1)) || isLetter(input.at(index + 1))) {
                        resultTable.push_back(TableRow(std::string("kisebb"), std::string("<")));
                        statePosition = 1;
                        index++;
                    }
                    else {
                        statePosition = 19;
                       
                    }
                   
                }
                else {
                    statePosition = 19;
                }

                break;
            }
            case 18: {
                if (!isIndexOutOfRange(index + 1, input)) {
                    if (input.at(index + 1) == '=') {
                        resultTable.push_back(TableRow(std::string("nagyobbegyenlo"), std::string(">=")));
                        statePosition = 1;
                        index += 2;
                    }
                    else if(isdigit(input.at(index + 1)) || isLetter(input.at(index + 1))) {
                        resultTable.push_back(TableRow(std::string("nagyobb"), std::string(">")));
                        statePosition = 1;
                        index++;
                    }
                    else {
                        statePosition = 19;
                    }

                }
                else {
                    statePosition = 19;
                }
               
                break;
            }
            case 19: {
                resultTable.push_back(TableRow(std::string("error at char: "+to_string(index+1)), std::string(1, input.at(index))));
                statePosition = 1;
                index++;
                break;
            }
               
            }

            //CHECK the string end
            if (isIndexOutOfRange(index, input)) {
                statePosition = 21;
            }
        } while (statePosition < 21);
        
    }

    std::vector<TableRow> getResultTable() {
        return this->resultTable;
    }



 private:

     void initState() {
         this->resultTable.clear();
     }

     int calculcateStatePosition(char inputChar) {
         int statePosition = 19;
         if (isdigit(inputChar)) {
             statePosition = 4;
         }

         else if (isLetter(inputChar)) {
             statePosition = 2;
         }
         else if (isSpecialChar(inputChar)) {
             switch (inputChar) {
             case '(':
                 statePosition = 8;
                 break;
             case '{':
                 statePosition = 6;
                 break;
             case ':':
                 statePosition = 13;
                 break;
             case '<':
                 statePosition = 15;
                 break;
             case '>':
                 statePosition = 18;
                 break;
             }
         }
         return statePosition;
     }

    bool isSpecialChar(char c) {
        for (int i = 0; i < this->specialCharacters.size(); i++) {
            if (specialCharacters[i] == c) {
                return true;
            }
        }
        return false;
    }

    bool isIndexOutOfRange(int index,const std::string& input) {
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


};


