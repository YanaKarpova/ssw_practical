#include <algorithm>
#include <iostream>
#include <chrono>
#include <list>
#include <map>
#include <vector>
#include "Variable.h"

class Syntax;

class Tree 
{
private:

	Tree* left_node;
	Tree* right_node;
	Tree* parent_node;
	std::string value;

public:

	friend Syntax;
	Tree();
	void printTree(Tree* tree);
	Tree* buildTreeStub(Tree* t_tree, const std::string& node_name);
	Tree* createNode(const std::string& node_name);
	void Alter_Node(const std::string& node_name);
	void createVarTree(Tree* t_tree, Tree* t_donor_tree, int lvl);
	void freeTreeNode(Tree*& t_tree);
}; 
