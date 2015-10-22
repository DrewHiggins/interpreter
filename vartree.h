// Variable Tree Header File
// A symbol table for variables will be represented here with 
// a binary tree, associating variable names with integer variables.
// The exterior interface will do nothing but assign to variables
// and look up their values, so the only purpose in having the
// structure definition here is to enable access to the overall tree.

#include <iostream>
#include <string>
using namespace std;

// A node anywhere in tree
class TreeNode
{
    friend ostream& operator<<( ostream&, TreeNode & );
    friend class VarTree;
    private:
	string	name;		// variable name
	int	value;		// variable value
	TreeNode *left,		// sub-tree for less than
		 *right;	// sub-tree for greater than

	// Private constructor: only for use by VarTree
	TreeNode( string newName , int val )
	{
	    name.assign( newName );	// get the name
	    value = val;		// and the value
	    left = right = NULL;	// no children
	}
};

// And a mechanism to store and retrieve entries in the tree.
class VarTree
{
    friend ostream& operator<<( ostream&, VarTree & );
    private:
	TreeNode *root;
    public:
        VarTree()
	{
	    root = NULL;	// empty tree
	}
	void assign( string, int );
	int lookup( string );

    private:		// these just help VarTree do its job
	TreeNode* recursiveSearch( TreeNode *&, string );
};

