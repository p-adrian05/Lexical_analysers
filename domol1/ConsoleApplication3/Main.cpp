

#include <iostream>
#include "Analyzer.cpp"

void printResult(std::vector<TableRow> resultTable) {
	std::cout << "Result: " << std::endl;
	for (int i = 0; i < resultTable.size(); i++) {
		std::cout << resultTable[i].toString() << std::endl;
	}
	std::cout << "\n" << std::endl;
}

int main()
{
	 std::string inputString ="asd:=23(*sdds*){asd}ad<=23<>ass";
	 Analyzer analyzer;
	 analyzer.analyze(std::string(inputString));

	 std::cout << "Sample input: "+ inputString << std::endl;
	 std::vector<TableRow> resultTable = analyzer.getResultTable();
	 printResult(analyzer.getResultTable());


	 while (true) {
		 std::cout << "Type input string: " << std::endl;
		 cin >> inputString;
		 analyzer.analyze(std::string(inputString));
		 std::vector<TableRow> resultTable = analyzer.getResultTable();
		 printResult(analyzer.getResultTable());
	 }
	 
}

