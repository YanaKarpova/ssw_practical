//
// Created by vovan on 28.09.2019.
//

#include "Syntax.h"

/**
 * Given grammar:
 * <Soft>                     ::= program <id> ; <block> .
 * <block>                    ::= <var part> <state part>
 * <var part>                 ::= var <var dec> : <type> [ = <exp> ] ;
 * <var dec>                  ::= <id> { , <var dec> }
 * <state part>               ::= <compound>
 * <compound>                 ::= begin <state> { ; <state> } end
 * <state>                    ::= <assign> | <compound> | < reiterate state>
 * <assign>                   ::= <id> := <exp> ;
 * <exp>                      ::= <id> | <constant> | <add> | <sub> | <mul> | <div> | <relational-operator>
 * <type>                     ::= integer
 * <id>                       ::= a-z
 * <constant>                 ::= 0-9
 *<reiterate state>           ::= repeat <state> {; <state>} until <relational-operator>  
 *<relational-operator>       ::= '==' | '<>' | '<' | '<=' | '>' | '>=' |
 * <equal>			          ::= <exp> == <exp>
 * <not equal>		          ::= <exp> <> <exp>
 * <less>			          ::= <exp> < <exp>
 * <less than or equal to>    ::= <exp> <= <exp>
 * <great>			          ::= <exp> > <exp>
 * <greater than or equal to> ::= <exp> >= <exp>
 * <add>		              ::= <exp> + <exp>
 * <sub>		              ::= <exp> - <exp>
 * <div>		              ::= <exp> /(div) <exp>
 * <mul>		              ::= <exp> * <exp>
 */


Syntax::Syntax(std::vector<Lexem>&& t_lex_table) 
{ 
	if (t_lex_table.empty())
		Error.printError(LEX_TABLE_ERR);
	//throw std::runtime_error("<E> Syntax: Lexemes table is empty");
	if (t_lex_table.at(0).GetToken() == eof_tk) 
		Error.printError(FILE_EMPTY_ERR);
	//throw std::runtime_error("<E> Syntax: Code file is empty");
	lex_table = t_lex_table;
	cursor = lex_table.begin();
}


Syntax::~Syntax() 
{ 
	pascal_tree->freeTreeNode(pascal_tree);
}


/**
 * XXX: Each block (..Parse) builds its subtree (and returns it),
 *   which is then added at a higher level, at the place of the method call.
 */ 

 /**
  * @brief Start parse incoming pascal file
  * @param none
  *
  * @return  EXIT_SUCCESS - if file was successful parsed
  * @return -EXIT_FAILURE - if can't parse incoming file
  */
int Syntax::ParseCode() 
{
	std::cout << "Code contains " << lex_table.size() << " lexemes" << std::endl;
	auto& it = cursor;
	if (programParse(it) != 0)
		return -EXIT_FAILURE;

	while (it != lex_table.end() && it->GetToken() != eof_tk)
		blockParse(it);
	std::cout << "EOF" << std::endl;

	return EXIT_SUCCESS;
}


/**
 * @brief Parse entry point in grammar
 * @param[inout] t_iter - iterator of table of lexeme
 *
 * @return  EXIT_SUCCESS - if input program part is correct
 * @return -EXIT_FAILURE - if input program part is incorrect
 * @note Wait input like: program <id_tk> ;
 */
int Syntax::programParse(lex_it& t_iter) 
{
	if (!checkLexem(t_iter, program_tk)) {
		Error.printError(MUST_BE_PROG, *t_iter);
		return -EXIT_FAILURE;
	}

	auto iter = getNextLex(t_iter);
	if (!checkLexem(iter, id_tk)) {
		if (iter->GetToken() == eof_tk) {
			Error.printError(EOF_ERR, *iter);
			return -EXIT_FAILURE;
		}
		else {
			Error.printError(MUST_BE_ID, *iter);
			return -EXIT_FAILURE;
		}
	}
	auto root_name = iter->GetName(); // save the name of program

	iter = getNextLex(t_iter);
	if (!checkLexem(iter, semi_tk)) {
		if (iter->GetToken() == eof_tk) {
			Error.printError(EOF_ERR, *iter);
			return -EXIT_FAILURE;
		}
		else {
			Error.printError(MUST_BE_SEMI, *iter);
			return -EXIT_FAILURE;
		}
	}

	// First phase is OK, we can start to build the tree 
	pascal_tree = pascal_tree->createNode(root_name);

	return EXIT_SUCCESS;
}


/**
 * @brief Parse block part
 * @param[inout] t_iter - iterator of table of lexeme
 *
 * @return  EXIT_SUCCESS - if block part is matched to grammar
 * @return -EXIT_FAILURE - if block part doesn't matched to grammar
 */
int Syntax::blockParse(lex_it& t_iter) 
{
	try {
		auto iter = getNextLex(t_iter);
		switch (iter->GetToken()) {
		case var_tk: {
			pascal_tree->left_node = pascal_tree->buildTreeStub(pascal_tree, "var");
			vardpParse(t_iter, pascal_tree->left_node);
			break;
		}
		case begin_tk: {
			pascal_tree->right_node = pascal_tree->buildTreeStub(pascal_tree, "begin");
			compoundParse(t_iter, pascal_tree->right_node);
			break;
		}
		case dot_tk: { 
			std::cout << "Program was parse successfully" << std::endl;
			break;
		}
		default: {
			break;
		}
		}
		pascal_tree->printTree(pascal_tree);
		std::cout << std::endl;
	}
	catch (const std::exception & exp) {
		std::cerr << "<E> Syntax: Catch exception in " << __func__ << ": "
			<< exp.what() << std::endl;
		return -EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


/**
 * @brief Parse variable declaration part
 * @param[inout] t_iter - iterator of table of lexeme
 * @param[inout] t_tree - subtree of part of variables
 *
 * @return  EXIT_SUCCESS - if variable declaration part is matched to grammar
 * @return -EXIT_FAILURE - if variable declaration part doesn't matched to grammar
 */
int Syntax::vardpParse(Syntax::lex_it& t_iter, Tree* t_tree) 
{
	// var_list contains list of variables from current code line
	auto var_list = vardParse(t_iter);
	if (!checkLexem(t_iter, ddt_tk)) {
		Error.printError(MUST_BE_COMMA, *t_iter);
	}

	auto type_iter = getNextLex(t_iter);
	if (!checkLexem(t_iter, type_tk)) {
		Error.printError(MUST_BE_TYPE, *t_iter);
	}

	getNextLex(t_iter);
	if (!checkLexem(t_iter, semi_tk)) {
		Error.printError(MUST_BE_SEMI, *t_iter);
	}

	updateVarTypes(var_list, type_iter->GetName());
    buildVarTree(var_list, t_tree, id_map);

	auto forwrd_lex = peekLex(1, t_iter);
	if (checkLexem(forwrd_lex, var_tk) || checkLexem(forwrd_lex, id_tk)) {
		if (checkLexem(forwrd_lex, var_tk))
			getNextLex(t_iter);
		vardpParse(t_iter, t_tree->right_node);
	}
	else {
		t_tree->freeTreeNode(t_tree->right_node->right_node); //removing the last excess $
	}

	return EXIT_SUCCESS;
}


/**
 * @brief Parse line of variables
 * @param[inout] t_iter - iterator of table of lexeme
 *
 * @return list of variables
 * @note For example, we have next code lines:
 *   program exp1;
 *   var
 *     a, b : integer;    // return { a, b }
 *     c, d, e : integer; // return { c, d, e }
 *   ...
 */
std::list<std::string> Syntax::vardParse(lex_it& t_iter) 
{
	auto iter = getNextLex(t_iter);
	if (!checkLexem(iter, id_tk)) {
		Error.printError(MUST_BE_ID, *iter);
		return std::list<std::string>();
	}

	if (isVarExist(iter->GetName())) Error.printError(DUPL_ID_ERR, *iter);
	else
		id_map.emplace(iter->GetName(), Variable("?", "?"));

	std::list<std::string> var_list;
	var_list.push_back(t_iter->GetName());

	iter = getNextLex(t_iter);
	if (checkLexem(iter, comma_tk)) 
		var_list.splice(var_list.end(), vardParse(t_iter));
	return var_list;
}


/**
 * @brief Parse compound part
 * @param[inout] t_iter - iterator of table of lexeme
 *
 * @return  EXIT_SUCCESS - if compound part is matched to grammar
 * @return -EXIT_FAILURE - if compound part doesn't matched to grammar
 */
int Syntax::compoundParse(lex_it& t_iter,Tree* t_tree) 
{
	static int compound_count = 0;
	compound_count++;
	int state_count = 0;
	std::string op = "op";
	op = op + std::to_string(compound_count) + "_" + std::to_string(state_count + 1);
	t_tree->right_node = pascal_tree->buildTreeStub(t_tree, op);
	while (t_iter->GetToken() != end_tk) {
		if (t_iter->GetToken() == eof_tk) {
			Error.printError(EOF_ERR, *t_iter);
			return -EXIT_FAILURE;
		}
		state_count++;
		if (state_count > 1)
		{
			op.pop_back();
			op += std::to_string(state_count);
			t_tree->right_node->right_node = pascal_tree->buildTreeStub(t_tree, op);
			t_tree = t_tree->right_node;
		}
		stateParse(t_iter, t_tree->right_node);
	}
	if (compound_count == 1) {
		if (checkLexem(peekLex(1, t_iter), unknown_tk) ||
			checkLexem(peekLex(1, t_iter), eof_tk)) {
			Error.printError(MUST_BE_DOT, *t_iter);
			return -EXIT_FAILURE;
		}
	}
	t_tree->right_node->Alter_Node("end");
	return EXIT_SUCCESS;
}


/**
 * @brief Parse state part
 * @param[inout] t_iter - iterator of table of lexeme
 *
 * @return  EXIT_SUCCESS - if state part is matched to grammar
 * @return -EXIT_FAILURE - if state part doesn't matched to grammar
 */
int Syntax::stateParse(lex_it& t_iter, Tree* t_tree) {
	std::string x = "";
	auto iter = getNextLex(t_iter);
	switch (iter->GetToken()) {
	case id_tk: {

		if (!isVarExist(iter->GetName())) { 
			Error.printError(UNKNOWN_ID, *t_iter);
			return -EXIT_FAILURE;
		}

		getNextLex(t_iter);
		if (!checkLexem(t_iter, ass_tk)) {
			Error.printError(MUST_BE_ASS, *t_iter);
			return -EXIT_FAILURE;
		}
		t_tree = t_tree->left_node;
		t_tree =pascal_tree->buildTreeStub(t_tree, ":=") ;
		t_tree->left_node = pascal_tree->buildTreeStub(t_tree, iter->GetName());
		expressionParse(t_iter, x);
		if (!checkLexem(t_iter, semi_tk)) { // we exit from expression on the ';'
			Error.printError(MUST_BE_SEMI, *t_iter);
			return -EXIT_FAILURE;
		}
		break;
	}
	case begin_tk: {
		t_tree->left_node = pascal_tree->buildTreeStub(t_tree, "begin") ;
		compoundParse(t_iter, t_tree->left_node);
		getNextLex(t_iter);
		if (!checkLexem(t_iter, semi_tk)) {
			Error.printError(MUST_BE_SEMI, *t_iter);
			return -EXIT_FAILURE;
		}
		break;
	}
	default: {
		break;
	}
	}

	return EXIT_SUCCESS;
}


/**
 * @brief Parse expression part
 * @param[inout] t_iter - iterator of table of lexeme
 *
 * @return  EXIT_SUCCESS - if expression part is matched to grammar
 * @return -EXIT_FAILURE - if expression part doesn't matched to grammar
 */
int Syntax::expressionParse(lex_it& t_iter, std::string& x)
{
	auto iter = getNextLex(t_iter);
	switch (iter->GetToken()) {
	case id_tk: {
		if (!isVarExist(iter->GetName()))
			Error.printError(UNKNOWN_ID, *t_iter);
	}
	case constant_tk: { // like a := 3 ... 
		x += iter->GetName();
		iter = getNextLex(t_iter); 
		switch (iter->GetToken()) {
		case add_tk:
		case sub_tk:
		case mul_tk:
		case div_tk: {
				if (iter->GetToken() == div_tk)
					x += "/";
				else
					x += iter->GetName();
				expressionParse(t_iter, x);
			break;
		}

		default: {
			break;
		}
		}
		break;
	}
	case sub_tk: { // like a := -3;

		if (!checkLexem((peekLex(1, t_iter)), constant_tk) && !checkLexem((peekLex(1, t_iter)), id_tk))
		{
			Error.printError(CONSTANT_OR_IDENTIFIER_ERR, *t_iter);
			return -EXIT_FAILURE;
		}
		x += "-"; 
		expressionParse(t_iter, x);
		break;
	}
	case opb_tk:  // like a := ( ... );
	{
		x += "(";
		expressionParse(t_iter, x);
		if (!checkLexem(t_iter, cpb_tk))
		{
			Error.printError(MUST_BE_CPB, *t_iter);
			return -EXIT_FAILURE;
		}
		x += ")";
		iter = getNextLex(t_iter);
		switch (iter->GetToken()) {
		case add_tk:
		case sub_tk:
		case mul_tk:
		case div_tk: {
			if (iter->GetToken() == div_tk)
				x += "/";
			else
				x += iter->GetName();
			expressionParse(t_iter, x);
			break;
		}
	
		default: {
			break;
		}
		}
		break;
	}
	default: {
		Error.printError(MUST_BE_ID, *t_iter);
		return -EXIT_FAILURE;
	}
	}

	return EXIT_SUCCESS;
}


 /**
  * @brief Get next lexeme
  * @param[inout] iter - cursor-iterator of lexeme table
  *
  * @return iterator on next lexeme
  */
Syntax::lex_it Syntax::getNextLex(lex_it& iter) {
	try {
		if (iter != lex_table.end())
			iter++;
	}
	catch (const std::exception & exp) {
		std::cerr << "<E> Syntax: Catch exception in " << __func__ << ": " 
			<< exp.what() << std::endl;
	}

	return iter;
}


/**
 * @brief Peek to forward on the N lexeme
 * @param[in] N      - the number of skipped tokens
 * @param[in] t_iter - copy of cursor-iterator of lexeme table
 *
 * @return copy of iterator on N-th lexeme (token)
 * @note If catch exception, return copy of iterator
 */
Syntax::lex_it Syntax::peekLex(int N, lex_it t_iter) {
	try {
		auto iter = t_iter;
		while (iter != lex_table.end()) {
			if (N == 0) return iter;
			iter++; N--;
		}

		return iter;
	}
	catch (const std::exception & exp) {
		Error.printError2(PEEK_ERR);
		//std::cerr << "<E> Syntax: Can't peek so forward" << std::endl; 
		return t_iter;
	}
}


/**
 * @brief Check does current lexeme is match to needed token
 * @param[in] t_iter - current lexem
 * @param[in] t_tok  - needed token
 *
 * @return true  - if lexeme is match
 * @return false - if lexeme is unreachable (end) or if doesn't match
 */
bool Syntax::checkLexem(const Syntax::lex_it& t_iter, const tokens& t_tok) {
	if (t_iter == lex_table.end())   return false;
	if (t_iter->GetToken() != t_tok) return false;

	return true;
}


/**
 * @brief Check existence of variable
 * @param[in] t_var_name - variable for check
 *
 * @return true  - if variable is exist
 * @return false - if unknown variable (doesn't exist)
 */
bool Syntax::isVarExist(const std::string& t_var_name) {
	auto map_iter = id_map.find(t_var_name);
	return !(map_iter == id_map.end());
}


/**
 * @brief Update information about type in map of identifiers
 * @param[in] t_var_list  - list of variables
 * @param[in] t_type_name - type of variables
 *
 * @return none
 */
void Syntax::updateVarTypes(const std::list<std::string>& t_var_list,
	const std::string& t_type_name) {
	try {
		for (auto& el : t_var_list)
			id_map.at(el).type = t_type_name;
	}
	catch (const std::exception & exp) {
		std::cerr << "<E> Syntax: Catch exception in " << __func__ << ": "
			<< exp.what() << std::endl;
	}
}


/**
 * @brief Build subtree of variable declaration part
 * @param[in]  t_var_list - list of variable
 * @param[out] t_tree     - subtree of variable part
 *
 * @return none
 * @note If we firstly call this method:
 *                              program_name
 *                               /         \
 *             t_tree here ->  var         <block>
 */
void Syntax::buildVarTree(const std::list<std::string>& t_var_list, Tree* t_tree, std::map<std::string, Variable> id_map)
{ 
	try {
		auto i = 0;
		for (auto& el : t_var_list) {
			Tree* tmp_tree = t_tree->createNode(el);
			tmp_tree->right_node = t_tree->buildTreeStub(tmp_tree, id_map.at(el).type);
			t_tree->createVarTree(t_tree, tmp_tree, i++);
		}
	}
	catch (const std::exception & exp) {
		std::cerr << "<E> Syntax: Catch exception in " << __func__ << ": "
			<< exp.what() << std::endl;
	}
}
