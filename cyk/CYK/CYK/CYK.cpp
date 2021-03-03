#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <windows.h>
#include <map>  
#include <algorithm>
#include <sstream>
class CYK {
    /**
     * This Matrix will be represt the CYK table. The elements
     * in the matrix make an uppper matrix
     */
private:
    std::string inputString;
    int inputStringLength;

public:

     CYK(std::string input) {
         this->inputString = input;
         this->inputStringLength = input.length();
    }

     void Run() {
         NonTerminal();
         SetUpCykTable();
         SetUpInputLine();
         ClearBottomTriangle();
         FirstRow();
         NextRows();
         Write();
         Success();
     }

private:
    std::string table[8][8];
  
    /**
     * Collect all Non-Terminals in the grammar.
     */
    std::vector<std::string> nonTerminals;


    std::map<std::string, std::string> grammar = {
        {"S","S"},
        {"S","AB"},
        {"A","CA"},
        {"A","SS"},
        {"B","CD"},
        {"A","b"},
        {"D","a"},
        {"C","c"},
        {"C","v"},
    };



    void Success() {
        if (table[0][inputString.length() - 1].find("S") != std::string::npos) {
            std::cout << "Levezetheto a\t!" + this->inputString << '\n';
        }
        else {
            std::cout << "Nem Levezetheto a\t!" + this->inputString << '\n';
        }
    }

    /**
     * Collecting all Non-Terminals in the grmmar
     * and add to {@link #NonTerminal()}
     */
     void NonTerminal() {
        for (char c = 'a'; c <= 'z'; c++) {
            for (std::map<std::string, std::string>::reverse_iterator ii = grammar.rbegin(); ii != grammar.rend(); ++ii)
            {
                if((*ii).second == std::string(c + " ")) {
                    nonTerminals.push_back((*ii).second);
                }
            }
        }
    }

    /**
     * Init the Table. Fill all space with "+" characters
     */
    void SetUpCykTable() {
        for (int i = 0; i < inputString.length() + 1; i++) {
            for (int j = 0; j < inputString.length(); j++) {
                table[i][j] = "+";
            }
        }
    }

    /**
     * Input as Diagonal to make fancy the output table :)
     * and make +1 width table
     */
     void SetUpInputLine() {
        for (int i = 1; i < inputString.length() + 1; i++) {
            for (int j = 0; j < inputString.length(); j++) {
                if (i == j + 1) {
                    table[i][j] = inputString.at(i - 1) + "";
                }
            }
        }
    }

    /**
     * Delete all charachers on the bottom triangle, we don't need that.
     */
     void ClearBottomTriangle() {
        for (int i = 1; i < inputString.length() + 1; i++) {
            for (int j = 0; j < inputString.length(); j++) {
                try {
                    if (i >= j + 2) {
                        table[i][j] = "";
                    }
                }
                catch (...) {
                    continue;
                }

            }
        }
    }

    /**
     *  Set the first line of the cyk table, in manually.
     */
     void FirstRow() {
        for (int i = 0; i < inputString.length() + 1; i++) {
            for (int j = 0; i < inputString.length(); j++) {
                try {
                    if (contains(nonTerminals, table[i][j])) {
                        table[i][j] = "";
                        for (std::map<std::string, std::string>::reverse_iterator ii = grammar.rbegin(); ii != grammar.rend(); ++ii)
                        {
                            if ((*ii).second == table[i][j] ) {
                                table[i][j] += (*ii).second;
                            }
                        } 
                    }
                }
                catch (...) {
                  break;
               }

            }
        }
    }
     bool contains(std::vector<std::string> arr,std::string arg) {
         return std::find(arr.begin(), arr.end(), arg) != arr.end();
     }
     int filterException(int code, PEXCEPTION_POINTERS ex) {
         std::cout << "Filtering " << std::hex << code << std::endl;
         return EXCEPTION_EXECUTE_HANDLER;
     }
    /**
     * Generate all Combinations of Non-Terminals
     *
      * @param First Non-Terminals
     * @param Second Non-Teminals
     * @return return First Non-TerminalsSecond Non-Teminals string
     */
     std::vector<std::string> AllCombinations(std::string s1, std::string s2) {
        std::vector<std::string> arr1 = split(s1, "");
        std::vector<std::string> arr2 = split(s2, "");
        std::vector<std::string> result;
        for (int i = 0; i < s1.length(); i++) {
            for (int j = 0; j < s2.length(); j++) {
                result.push_back(std::string(arr1[i] + arr2[j]));
            }
        }
        return result;
    }
     // for string delimiter
     std::vector<std::string> split(std::string s, std::string delimiter) {
         size_t pos_start = 0, pos_end, delim_len = delimiter.length();
         std::string token;
         std::vector<std::string> res;

         while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
             token = s.substr(pos_start, pos_end - pos_start);
             pos_start = pos_end + delim_len;
             res.push_back(token);
         }

         res.push_back(s.substr(pos_start));
         return res;
     }
    /**
     * Based on first level and make a cyk table.
     */
    void NextRows() {
        for (int j = 0; j < inputString.length(); j++) {
            int stepper = 0;
            for (int i = 0; i < inputString.length(); i++) {
                if (table [stepper][i]=="+") {
                    int index_helper = 1;
                    std::string builder = "";
                    while (!contains(nonTerminals, table[stepper + index_helper][i])) {
                        std::vector<std::string> temp
                            = AllCombinations(
                                table[stepper][i - index_helper],
                                table[i + 1 - index_helper][i]);
                        index_helper++;
                        for (std::map<std::string, std::string>::reverse_iterator ii = grammar.rbegin(); ii != grammar.rend(); ++ii)
                        {
                            if (contains(temp,(*ii).second)) {
                                builder += (*ii).second;
                            }
                        }
                    }
                    if (builder=="") {
                        table[stepper][i] = "-";
                    }
                    else {
                        table[stepper][i] = builder;
                    }
                    stepper++;
                }

            }
        }
    }

    /**
     * Print the Table to console.
     */
     void Write() {
        for (int i = 0; i < inputString.length() + 1; i++) {
            for (int j = 0; j < inputString.length(); j++) {
                std::cout << table[i][j];
            }
            std::cout << "\n " << std::endl;

        }
    }


};