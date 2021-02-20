#pragma once
#include <iostream>
class TableRow
{
	std::string token;

	std::string lexema;

	TableRow(std::string& token, std::string& lexema) {
		this->token = token;
		this->lexema = lexema;
	}

	std::string toString() {
		return token + "==" + lexema;
	}
};

