#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <map>  
#include <algorithm>
#include <sstream>
#include <string.h>

class CYK {
	private:
    //Insert grammer here

       std::vector<std::vector<std::string>> grammer;
    //Checks if the passed string can be achieved for the grammer
    std::string checkIfInGrammer(std::string a){
        std::string to_ret = "";
        int count = 0;
        for(int i = 0; i < grammer.size(); i++){
            for(count = 0; count < grammer[i].size(); count++){
                if(a.compare(grammer[i][count]) == 0){
                    to_ret.append(grammer[i][0]);
                }
            }
        }
        return to_ret;
    }
    
    //Makes all possible combinations out of the two string passed
   std::string combinateAndCheck(std::string a, std::string b){
        std::string to_ret = "", temp = "";
            for(int i = 0; i < a.length(); i++){
                for(int j = 0; j < b.length(); j++){
                    temp = "";
                    temp.append(std::string(1,a.at(i)));
                    temp.append("");
                     temp.append(std::string(1, b.at(j)));
                    to_ret.append(checkIfInGrammer(temp));
                }
            }
        return to_ret;
    }
	int indexof(std::string& text, std::string& pattern)
    {
        // where appears the pattern in the text?
        std::string::size_type loc = text.find(pattern, 0);
        if(loc != std::string::npos)
        {
            return loc;
        }
        else
        {
            return -1;
        }
    }
	public:

    CYK(){

    }
    CYK( std::vector<std::vector<std::string> > grammer){
        this->grammer = grammer;
    }
	bool analyze(std::string str){
		   std::string finish;
        int n = 0;
        //Start symbol is generally "S"
        finish = "S";
        std::string temp;
		std::string st = "", r = "";
        int count;
        std::string matrix[str.length()+1][str.length()+1];

		 for(int i = 0; i < str.length(); i++){
            r = "";
            st = str.at(i);
            for(int j = 0; j <  grammer.size(); j++){
                for(count = 1; count < grammer[j].size(); count++){
                    if(st.compare(grammer[j][count])==0){
                        r.append(grammer[j][0]);
                    }
                }      
            }
            matrix[i][i] = r;
        }
	 
        //Fill the rest of the matrix
        for(int i =1; i < str.length(); i++){
            for(int j = i; j < str.length(); j++){
                r = "";
                for(int k = j - i; k < j; k++){
                    r.append(combinateAndCheck(matrix[j - i][k], matrix[k + 1][j]));
                }
                matrix[j - i][j] = r;
    
            }
        }
         std::cout << "Matrix: " << std::endl;
       for (int i = 0; i < str.length() + 1; i++) {
            for (int j = 0; j < str.length(); j++) {
                std::cout << matrix[i][j];
            }
            std::cout << "\n" << std::endl;
        }
        
         
        //The last column of first row should have the start symbol
        if(indexof(matrix[0][str.length() - 1],finish) >= 0){
            return true;
        }
        else{
           return false;
        }

	}
};