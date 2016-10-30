#include <iostream>
#include <fstream>
#include "AdditionalFunctions.h"

int main( int argc, char *argv[] )
{
	if(argc > 2 || argv[0] == NULL || argv[1] == NULL )
	{
		std::cerr << "Error! Bad input!\n";
		return 1;
	}

	//argv[0]->expression, argv[1]->file name/path
	char* expression = argv[0];
	if(!isValid(expression))
	{
		std::cerr << "Expression is not valid!";
		return 1;
	}
	
	std::fstream file;
	file.open(argv[1], std::fstream::in);
	if(!file.good())
	{
		std::cerr << "\nUnable to open/create file!\n\n";
		return 1;
	}
	
	operInfo opFromFile[50];
	readTo(file,opFromFile);

	int length = strlen(expression);
	char* convertedExpr = new char[length];

	convertExpr(expression, convertedExpr, opFromFile);
	std::cout << "Result is: " << calculate(convertedExpr, opFromFile) << std::endl;

	file.close();

	return 0;
}