// Variable Tree Implementation File
// This is a simple binary search tree associating variables
// with integer values.
#include <iostream>
#include <string>
using namespace std;

#include "vartree.h"

//  recursiveSearch
//  A recursive tree-traversal function to search for a variable.
//  If the variable does not exist, it is created with a value of 0.
//  Parameters:
//  	node	(modified TreeNode ptr)	root of sub-tree to search
//  	name	(input string)			name of variable
//  NOTE: node May be a null pointer, indicating an empty tree
//  Post-condition:
//      node points at a node with the given name,
//      even if it had to be created to do so
TreeNode* VarTree::recursiveSearch( TreeNode *&node, string name )
{
	if (node)
    {
    	if (node->name == name) // found the node
            return node;
        else // keep looking
        {
            if (name < node->name) // search left
                return recursiveSearch( node->left, name );
            else 				   // search right
                return recursiveSearch( node->right, name );
        }
    }
    else
    {
        TreeNode *newNode = new TreeNode( name, 0 );
        node = newNode;
        if (root == NULL) // if the tree is empty, this is the root
            root = newNode;
        return newNode;
    }
}

//  lookup
//  Searches for a variable to get its value
//  If the variable does not yet exist, it is created with value 0.
//  Parameters:
//  	name	(input char array)	name of variable
//  Returns:				value of variable
int VarTree::lookup( string name )
{
    TreeNode *node = recursiveSearch( root, name );
    return node->value;
}

//  assign
//  Assigns a value to a variable.
//  If the variable does not yet exist, it is created.
//  Parameters:
//  	name	(input string)		name of variable
//  	value	(input integer)		value to assign
void VarTree::assign( string name, int value )
{
    TreeNode *node = recursiveSearch( root, name );
    node->value = value;
}

//  EXTRA CREDIT:  Implement the following, without any loops
ostream& operator<<( ostream& stream, VarTree &vt )
{
	return stream;
}

ostream& operator<<( ostream& stream, TreeNode &tn )
{
    return stream;
}
