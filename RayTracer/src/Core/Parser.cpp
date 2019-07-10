#include "Parser.h"


Parser::Parser()
{
}

Parser::~Parser()
{
}
std::string Parser::Parse(std::string path)
{
	std::string inputText;
	std::ifstream inputStream(path);

	std::string line;
	while (std::getline(inputStream, line))
	{
		std::istringstream iss(line);
	}




	return inputText;
}
