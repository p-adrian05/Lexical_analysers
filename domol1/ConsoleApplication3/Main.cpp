

#include <iostream>
#include "Analyzer.cpp"

void printResult(std::vector<TableRow> table) {
	std::cout << "Eredmeny: " << std::endl;
	for (int i = 0; i < table.size(); i++) {
		std::cout << table[i].getToken();
	}
	std::cout << "\n " << std::endl;
	
}

void printErrors(std::vector<TableRow> table) {
	std::cout << "Hibak: " << std::endl;
	for (int i = 0; i < table.size(); i++) {
		std::cout << table[i].toString();
	}
	std::cout << "\n " << std::endl;

}

int main()
{
	 std::string inputString ="antal12<>12antal{komment}:=12(*komment2*)23>=antal<=12";
	 Analyzer analyzer;
	 analyzer.analyze(std::string(inputString));

	 std::cout << "Minta input:  "+ inputString << std::endl;
	 printResult(analyzer.getResultTable());
	 if (analyzer.getErrorTable().size() != 0) {
		 printErrors(analyzer.getErrorTable());
	 }

	 while (true) {
		 std::cout << "Adjon meg egy stringet! " << std::endl;
		 getline(cin, inputString);
		 analyzer.analyze(std::string(inputString));
		 printResult(analyzer.getResultTable());
		 if (analyzer.getErrorTable().size() != 0) {
			 printErrors(analyzer.getErrorTable());
		 }
	 }
	 
}

