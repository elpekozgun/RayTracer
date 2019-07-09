
#include <iostream>
#include "Parser.h"
#include <algorithm>
#include <iterator>

using namespace std;

struct vector2
{
	float x;
	float y;
};

struct vector3
{
	float x;
	float y;
	float z;
};

struct vector4
{
	float x;
	float y;
	float z;
	float w;
};



int main()
{
	string output = Parser::Parse("res/input1.txt");
	


	return 0;
};