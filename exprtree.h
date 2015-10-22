//  Expression Tree Header File
//  Describes the elements of an expression tree, using
//  derived classes to represent polymorphism.
//  All objects in this structure are immutable --
//  once constructed, they are never changed.
//  They only be displayed or evaluated.
#include <iostream>
using namespace std;
#include "vartree.h"
#include "funmap.h"

class ExprNode
{
    public:
    friend ostream& operator<<( ostream&, const ExprNode & );
    virtual string toString() const = 0;	// facilitates << operator
    virtual int evaluate( VarTree &v, FunctionDef &f ) const = 0;  // evaluate this node
};

class Value: public ExprNode
{
    private:
	int value;
    public:
	string toString() const;	// facilitates << operator
	int evaluate( VarTree &v, FunctionDef &f ) const;
	Value(int v)
	{
	    value = v;
	}
};

class Variable: public ExprNode
{
    private:
	string name;
    public:
	string toString() const ;	// facilitates << operator
	int evaluate( VarTree &v, FunctionDef &f ) const;
	Variable(string var)
	{
	    name = var;
	}
};

class Operation: public ExprNode
{
    private:
	string oper;
	ExprNode *left, *right;	 // operands
    public:
	string toString() const;	// facilitates << operator
	int evaluate( VarTree &v, FunctionDef &f ) const;
	Operation( ExprNode *l, string o, ExprNode *r )
	{
	    left = l;
	    right = r;
	    oper = o;
	}
};

class Conditional: public ExprNode
{
    private:
	ExprNode *test, *trueCase, *falseCase;
    public:
	string toString() const;	// facilitates << operator
	int evaluate( VarTree &v, FunctionDef &f ) const;
	Conditional( ExprNode *b, ExprNode *t, ExprNode *f )
	{
	    test = b;
	    trueCase = t;
	    falseCase = f;
	}
};

class Function: public ExprNode
{
    private:
    string name;
    ExprNode* param[10];
    int paramSize = 0;
    public:
    string toString() const;
    int evaluate( VarTree &v, FunctionDef &f ) const;
    Function( string n, ExprNode* p[10], int s ) : name(n), paramSize(s) {
        copy(p, p+10, param);
    }
};
