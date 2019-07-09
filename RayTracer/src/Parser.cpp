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
	std::ifstream inputContext;
	inputContext.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	
	inputContext.open(path);
	//std::stringstream inputStream;
	//inputStream << inputContext.rdbuf();
	//inputContext.close();
	//inputText = inputStream.str();

	std::string line;
	std::string asd;
	while (std::getline(inputContext, line))
	{
		std::istringstream iss(line);
		asd = iss.str();

		if (asd == "#AmbientLight")
		{
			float dsa = 5;
		}

	}







	return inputText;
}
