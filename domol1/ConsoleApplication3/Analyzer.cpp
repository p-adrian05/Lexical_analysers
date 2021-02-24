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
using namespace std;

class Analyzer
{
private:
    const std::vector<char> specialCharacters = { '{', '}', '(', '*', ')', ':', '=', '<', '>', };
    std::vector<TableRow> resultTable;
    std::vector<TableRow> errorTable;

public:
    Analyzer() {
        initState();
    }

    void analyze(const std::string& input) {
        initState();
        int statePosition = 1;
        int index = 0;
        do {
           
            while (isspace(input.at(index))) {
                index++;
            }
            if (isIndexOutOfRange(index, input)) {
                statePosition = 21;
            }
            if (statePosition==1) {
                 statePosition = calculcateStatePosition(input.at(index));
            }
            if (statePosition == 21) {
                return;
            }
           
            
            switch (statePosition) {
            case 2: {
               
                std::string lexema = "";
                while (!isIndexOutOfRange(index,input) && isLetterOrDigit(input.at(index))){
                    lexema += input.at(index);
                    index++;
                }
                statePosition = 1;
                resultTable.push_back(TableRow(std::string("<azonosito>"), lexema));
                break;
            }
            case 4: {
               
                std::string lexema = "";
                while (!isIndexOutOfRange(index,input) && isdigit(input.at(index))) {
                    lexema += input.at(index);
                    index++;
                }
                statePosition = 1;

                resultTable.push_back(TableRow(std::string("<konstans>"), lexema));
                break;
            }
            case 6: {
              
                std::string lexema = "";
                index++;
                while (!isIndexOutOfRange(index, input) && input.at(index) != '}') {
                    lexema += input.at(index);
                    index++;
                }
                statePosition = 1;
                index++;

                resultTable.push_back(TableRow(std::string("<{}kommentar>"), lexema));
                break;
            }
            case 8: {
                             
                if (!isIndexOutOfRange(index + 1, input)) {
                    if (input.at(index + 1) == '*') {
                        std::string lexema = "";
                        index += 2;
                        while (!isIndexOutOfRange(index, input)) {
                            if (input.at(index) == '*') {
                                if (!isIndexOutOfRange(index + 1, input)) {
                                    if (input.at(index + 1) == ')') {

                                        resultTable.push_back(TableRow(std::string("<(**)kommentar>"), lexema));
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

                        resultTable.push_back(TableRow(std::string("<ertekadasjel>"), std::string(":=")));
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
                        resultTable.push_back(TableRow(std::string("<kisebbegyenlo>"), std::string("<=")));
                        statePosition = 1;
                        index += 2;
                    }
                    else if (input.at(index+1) == '>') {
                        resultTable.push_back(TableRow(std::string("<nemegyenlo>"), std::string("<>")));
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
            case 18: {
                if (!isIndexOutOfRange(index + 1, input)) {
                    if (input.at(index + 1) == '=') {
                        resultTable.push_back(TableRow(std::string("<nagyobbegyenlo>"), std::string(">=")));
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
            case 19: {
                std::string errorMessage = std::string("at index: ");
                std::string errorIndex = to_string(index);
                errorMessage.append(errorIndex);
                std::string errorValue = std::string(1,input.at(index));
                errorTable.push_back(TableRow(errorMessage, errorValue));
                statePosition = 1;
                index++;
                break;
            }
            
               
            }

            if (isIndexOutOfRange(index, input)) {
                statePosition = 21;
            }
        } while (statePosition != 21);
        
    }

    std::vector<TableRow> getResultTable() {
        return this->resultTable;
    }

    std::vector<TableRow> getErrorTable() {
        return this->errorTable;
    }



 private:

     void initState() {
         this->resultTable.clear();
         this->errorTable.clear();
     }

     int calculcateStatePosition(char inputChar) {
         int statePosition = 19;
         if (isdigit(inputChar)) {
             statePosition = 4;
         }
         if (inputChar == '$') {
             statePosition = 21;
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
    bool isLetterOrDigit(char c) {
        return isLetter(c) || isdigit(c);
    }


};


