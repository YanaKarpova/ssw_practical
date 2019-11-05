//
// Created by vovan on 28.09.2019.
//

 #ifndef LECS_PARS_LEXEM_H
#define LECS_PARS_LEXEM_H

#include <string>


enum tokens 
{
    unknown_tk = -1,    // we get unknown token
    program_tk = 0,     // 'program'
    var_tk,             // 'var'
    begin_tk,           // 'begin'
    end_tk,             // 'end'
    type_tk,            // 'type'
    id_tk       = 8,    // any [aA-zZ][0-9]
    constant_tk = 9,    // 0-9
    dot_tk,             // '.'
    comma_tk,           // ','
    ddt_tk,             // ':'
    semi_tk,            // ';'
    eqv_tk,             // '='
    ass_tk,             // ':='
    add_tk,             // '+'
    sub_tk,             // '-'
    mul_tk,             // '*'
    div_tk,             // '/'
    opb_tk,             // '('
    cpb_tk,             // ')'

    eof_tk
};


enum errors 
{
      UNKNOWN_LEXEM,   // Unknown lexeme
      EOF_ERR,         // End of file error 
      MUST_BE_ID,      // Error: Must be identifier
      MUST_BE_SEMI,    // Error: Must be ';'
      MUST_BE_PROG,    // Error: Must be 'program'
      MUST_BE_COMMA,   // Error: Must be ','
      MUST_BE_TYPE,    // Error: Must be type of identifier 
      MUST_BE_DOT,     // Error: Must be '.'
      MUST_BE_ASS,     // Error: Must be ':='
      DUPL_ID_ERR,     // Error: Duplicate declaration on identifier
      UNKNOWN_ID,      // Error: Undefined identifier
      MUST_BE_VAR,  // Error: Must be 'var'
	  MUST_BE_BIGIN,  // Error: Must be 'begin'
	  MUST_BE_END,  // Error: Must be 'end'
	  MUST_BE_DDT,   // Error: Must be ':'
	  CONSTANT_OR_IDENTIFIER_ERR,  // Error: Must be 0-9 (constant) or identifier
	  EQF_ERR,  // Error: Must be '='
	  ADD_ERR,  // Error: Must be '+
	  SUB_ERR,  // Error: Must be '-'
	  MUL_ERR,  // Error: Must be '*'
	  DIV_ERR,  // Error: Must be '/'
	  MUST_BE_CPB,  // Error: Must be ')'
	  MUST_BE_OPB, //   Error: Must be '('
	  UNKNOWN_TK, // Unknown token
	  FILE_OPEN_ERR, // Unable to open file 
	  FILE_IS_OPEN_ERR, // The file is already open
	  FILE_CLOSE_ERR, // File close
	  FILE_FIlE_ERR, // Error reading file
	  FILE_EMPTY_ERR, // Code fail is empty
	  PEEK_ERR, // Can not  peek
	  LEX_TABLE_ERR // Lexem table is empty
};


class Lexem 
{
public: 
    Lexem() : name(""), token(unknown_tk), line(0) {};
    Lexem(std::string &&t_name, tokens t_tok, int t_line) : name(t_name),
                                              token(t_tok), line(t_line) {};

    std::string GetName();
    tokens      GetToken();
    int         GetLine();
private:
    std::string name;
    tokens      token;
    int         line;
};


#endif //LECS_PARS_LEXEM_H

