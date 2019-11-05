
#include "Tree.h"


Tree::Tree()
{
	left_node = nullptr;
	right_node = nullptr;
	 parent_node = nullptr;
}
void Tree::printTree(Tree* tree)
{
	if (tree == nullptr)
	{
		std::cout << ".";
		return;
	}
	std::cout << tree->value;
	printTree(tree->left_node);
	printTree(tree->right_node);
}
void Tree::Alter_Node(const std::string& node_name)
{
	value = node_name;
}


/**
 * @brief Create node of syntax tree
 * @param[in] t_tree    - parent node
 * @param[in] node_name - name of the created node (value)
 *
 * @return node of tree
 */
Tree* Tree::buildTreeStub(Tree* t_tree, const std::string& node_name) 
{
	auto* tree = new Tree;
	tree->value = node_name;
	tree->parent_node = std::addressof(*t_tree); // get address of parent node
	
	return tree;
}


/**
 * @brief Create like a root node of syntax tree
 * @param[in] node_name - name of the node (value)
 *
 * @return node of tree
 */
 Tree* Tree::createNode(const std::string& node_name) 
 {
	auto* tree = new Tree;
	tree->value = node_name;
	return tree;
}



void Tree::createVarTree(Tree* t_tree, Tree* t_donor_tree, int lvl) 
{
	if (lvl > 0) {
		lvl--;
		createVarTree(t_tree->right_node, t_donor_tree, lvl);
	}
	else {
		t_tree->left_node = t_donor_tree;
		t_tree->right_node = buildTreeStub(t_tree, "$");
	}
}


/**
 * @brief Free allocated (deallocate) memory
 * @param[in] t_tree - node of tree
 *
 * @return none
 */
void Tree::freeTreeNode(Tree*& t_tree) 
{
	try {
		if (t_tree->left_node != nullptr) freeTreeNode(t_tree->left_node);
		if (t_tree-> right_node!= nullptr) freeTreeNode(t_tree->right_node);
		delete t_tree;
		t_tree = nullptr;
	}
	catch (const std::exception & exp) {
		std::cerr << "<E> Syntax: Catch exception in " << __func__ << ": "
			<< exp.what() << std::endl;
	}
}
