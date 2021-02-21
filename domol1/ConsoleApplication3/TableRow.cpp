
#include <iostream>
class TableRow
{
private:
	std::string token;

	std::string lexema;

public:
	TableRow() {
	}

	 TableRow(std::string token, std::string lexema) {
		this->token = token;
		this->lexema = lexema;
	}

	std::string toString() {
		return token +  " == " + lexema;
	}
};