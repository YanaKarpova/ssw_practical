#include <fstream>
#include <iostream>
#include <string>
#include "Lexem.h"


struct Errors 
{
public:
	void printError(errors t_err, Lexem lex);
	void printError2(errors t_err);
};
