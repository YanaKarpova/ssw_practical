#include <fstream>
#include <iostream>
#include <string>
#include "Lexem.h"


struct Errors 
{
	void printError(errors t_err, Lexem lex);
	void printError(errors t_err);
};
