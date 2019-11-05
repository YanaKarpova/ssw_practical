//
// Created by vovan on 28.09.2019.
//

 #ifndef LECS_PARS_SYNTAX_H
#define LECS_PARS_SYNTAX_H

#include <algorithm>
#include <iostream>
#include <chrono>
#include <list>
#include <map>
#include <vector>
#include "Lexem.h"
#include "Lexer.h"
#include "Tree.h"
#include "Variable.h"

class Syntax 
{
public:
    explicit Syntax(std::vector<Lexem> &&t_lex_table);
    int ParseCode();
    ~Syntax();

private:
	
	using lex_it = std::vector<Lexem>::iterator; // alias of vector interator
    lex_it                          cursor;
    std::vector<Lexem>              lex_table; // out table of lexemes
    std::map<std::string, Variable> id_map; // out table of identifiers
    Tree  *pascal_tree; // our syntax tree
	Errors Error;

    lex_it getNextLex(lex_it &iter);
    lex_it peekLex(int N, lex_it t_iter);
	void buildVarTree(const std::list<std::string>& t_var_list, Tree* t_tree, std::map<std::string, Variable> id_map);
    int   expressionParse            (lex_it &t_iter, std::string& x);
    int   stateParse                 (lex_it &t_iter, Tree* t_tree);
    int   compoundParse              (lex_it &t_iter, Tree* t_tree);
    int   vardpParse                 (lex_it &t_iter, Tree *t_tree);
    std::list<std::string> vardParse (lex_it &t_iter);
    int   blockParse                 (lex_it &t_iter);
    int   programParse               (lex_it &t_iter);
    bool checkLexem    (const lex_it &t_iter, const tokens &t_tok);
    bool isVarExist    (const std::string &t_var_name);
    void updateVarTypes(const std::list<std::string> &t_var_list,
                        const std::string &t_type_name); 
};


#endif //LECS_PARS_SYNTAX_H
