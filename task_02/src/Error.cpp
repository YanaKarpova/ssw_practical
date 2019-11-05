#include "Error.h"

void Errors :: printError(errors t_err, Lexem lex)  // error information output
{ 
	switch (t_err) 
	{
	case UNKNOWN_LEXEM: 
	{
		std::cerr << "<E> Lexer: Get unknown lexem '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case EOF_ERR: 
	{
		std::cerr << "<E> Syntax: Premature end of file" << std::endl;
		break;
	}
	case MUST_BE_ID: 
	{
		std::cerr << "<E> Syntax: Must be identifier instead '" << lex.GetName() 
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case MUST_BE_SEMI:
	{
		std::cerr << "<E> Syntax: Must be ';' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case MUST_BE_PROG: 
	{
		std::cerr << "<E> Syntax: Program must start from lexem 'program' ("
			<< lex.GetLine() << ")" << std::endl;
		break;
	}
	case MUST_BE_COMMA: 
	{
		std::cerr << "<E> Syntax: Must be ',' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case DUPL_ID_ERR: 
	{
		std::cerr << "<E> Syntax: Duplicate identifier '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case UNKNOWN_ID:
	{
		std::cerr << "<E> Syntax: Undefined variable '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case MUST_BE_DOT:
	{
		std::cerr << "<E> Syntax: Program must be end by '.'" << std::endl;
		break;
	}
	case  MUST_BE_ASS: 
	{
		std::cerr << "<E> Syntax: Must be ':=' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case MUST_BE_TYPE:
	{
		std::cerr << "<E> Syntax: Must be type of identifier instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case MUST_BE_VAR:
	{
		std::cerr << "<E> Syntax: Must be 'var' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case  MUST_BE_BIGIN:
	{
		std::cerr << "<E> Syntax: Must be 'begin' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case  MUST_BE_END: 
	{
		std::cerr << "<E> Syntax: Must be 'end' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case  MUST_BE_DDT: 
	{
		std::cerr << "<E> Syntax: Must be ':' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case CONSTANT_OR_IDENTIFIER_ERR:
	{
		std::cerr << "<E> Syntax: Must be 0-9 (constant) or identifier instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case  EQF_ERR: 
	{
		std::cerr << "<E> Syntax: Must be '=' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case   ADD_ERR: 
	{
		std::cerr << "<E> Syntax: Must be '+' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case   SUB_ERR: 
	{
		std::cerr << "<E> Syntax: Must be '-' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case   MUL_ERR: 
	{
		std::cerr << "<E> Syntax: Must be '*' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case   DIV_ERR:
	{
		std::cerr << "<E> Syntax: Must be '/(div)' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case MUST_BE_CPB: 
	{
		std::cerr << "<E> Syntax: Must be ')' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	case MUST_BE_OPB:
	{
		std::cerr << "<E> Syntax: Must be '(' instead '" << lex.GetName()
			<< "' on " << lex.GetLine() << " line" << std::endl;
		break;
	}
	default: 
	{
		std::cerr << "<E> Syntax: Undefined type of error" << std::endl;
		break;
	}
	}
}


	void Errors::printError2(errors t_err) // error information output
	{ 
		switch (t_err) 
		{
		case UNKNOWN_TK: 
		{
			std::cerr << "<E> Unknown token" << std::endl;
			break;
		}
		case  FILE_OPEN_ERR:
		{
			std::cerr << "<E> Can't open file" << std::endl;
			break;
		}
		case  FILE_IS_OPEN_ERR: 
		{
			std::cerr << "<E> The file is already open" << std::endl;
			break;
		}
		case   FILE_CLOSE_ERR:
		{
			std::cerr << "<E> The file is close" << std::endl;
			break;
		}
		case FILE_FIlE_ERR: 
		{
			std::cerr << "<E> Can't read from the file" << std::endl;
			std::cerr << "File doesn't available" << std::endl;
			break;
		}
		case FILE_EMPTY_ERR:
		{
			std::cerr << "<E> Syntax: Code file is empty" << std::endl;
			break;
		}
		case PEEK_ERR: 
		{
			std::cerr << "<E> Syntax: Can't peek so forward" << std::endl;
			break;
		}
		case LEX_TABLE_ERR: 
		{
			std::cerr << "<E> Syntax: Lexemes table is empty" << std::endl;
			break;
		}
		case EOF_ERR: 
		{
			std::cerr << "File is EOF early" << std::endl;
			break;
		}
		default: 
		{
			std::cerr << "<E> Syntax: Undefined type of error" << std::endl;
			break;
		}
		}
	}
