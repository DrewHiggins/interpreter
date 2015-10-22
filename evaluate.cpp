// Simple Expression Evaluation Implementation file
// This describes the functionality for evaluating arithmetic expressions.
// Given a string consisting of opers and operands (integer or variable),
// it will evaluate that expression and return its value.
//
// The expressions may consist of the following:
// -- single-digit integer values
// -- simple arithmetic opers ( +, -, *, /, % )
// -- matched parentheses for grouping
// -- assignmnet operators for string variables ( = )

// This implementation consists of a set of mutually-recursive
// functions using an expression tree.

#include <iostream>
using namespace std;
#include "tokenlist.h"
#include "exprtree.h"
#include "funmap.h"

ExprNode* buildAssignment( ListIterator&, VarTree&, FunctionDef& );
ExprNode* buildConditional( ListIterator&, VarTree&, FunctionDef& );
ExprNode* buildProduct( ListIterator&, VarTree&, FunctionDef& );
ExprNode* buildSum( ListIterator&, VarTree&, FunctionDef& );
ExprNode* buildParentheses( ListIterator&, VarTree&, FunctionDef& );
ExprNode* buildFunctionOrVariable( ListIterator&, VarTree&, FunctionDef& );

// Evaluate
// Begins to tokenize the string, and then recursively evaluates it.
int evaluate( const char str[], VarTree &vars, FunctionDef &funs )
{
    TokenList *tokens = new TokenList( str );
    ListIterator iter = tokens->begin();
	ExprNode *root = buildAssignment( iter, vars, funs );
    if (root != NULL)
        return root->evaluate( vars, funs );
    else
        return 1;
}

// BuildAssignment
// Builds a subtree with the '=' operator at the root.
// Precondition: the expression must be properly formatted, in that,
//  since the '=' operator has lower precedence than arithmetic ones,
//  it can only be used as the only operation in an expression or as
//  an expression isolated within parentheses.
ExprNode* buildAssignment( ListIterator &iter, VarTree &vars, FunctionDef &funs )
{
    // if the first thing is a variable
    if (iter.tokenChar() != '(' && !iter.currentIsInteger())
    {
        ListIterator temp = iter; // make a copy
        temp.advance(); // move forward to check for an '='
        if (&temp.token() && temp.token().tokenText() == "=") 
                    // there is an assignment taking place and 
                    // the next token exists
        {
            ExprNode* left = new Variable( iter.token().tokenText() );
            iter.advance(); //advance to '='
            iter.advance(); // advance past '='
            ExprNode* right = buildAssignment( iter, vars, funs );
            if (&iter.token() && iter.tokenChar() == '?')
            {
                iter.advance(); // move past '?'
                ExprNode* tCase = buildAssignment( iter, vars, funs );
                iter.advance(); // move past ':'
                ExprNode* fCase = buildAssignment( iter, vars, funs );
                ExprNode* cond = new Conditional( right, tCase, fCase );
                return new Operation( left, "=", cond );
            }
            ExprNode* root = new Operation( left, "=", right );
            return root;
        }
    }
    // otherwise, there is no variable assignment
    return buildConditional( iter, vars, funs );
}

// BuildConditional
// Builds a tree with a conditional test operator (>, <, >=, <=, ==, or !=)
//  at its root. When evaluated, it will either return 1 (true) or 0 (false),
//  by default or something defined by the '?' and ':' operators.
ExprNode* buildConditional( ListIterator &iter, VarTree &vars, FunctionDef &funs )
{
    ExprNode* left = buildSum( iter, vars, funs );
    string oper = " ";
    if (&iter.token()) // check for the current token being a null reference
        oper = iter.token().tokenText();
    if (oper == "==" || oper == "<=" || oper == ">=" || oper == ">" ||
        oper == "<" || oper == "!=")
    {
        string oper = iter.token().tokenText();
        iter.advance();
        ExprNode* cond =  new Operation(left, oper, buildAssignment(iter, vars, funs) );
        ListIterator temp = iter;
        if (&temp.token() && temp.tokenChar() == '?') // see if there is another
                                                      // token that is a '?'
        {
            iter.advance(); // move past '?'
            ExprNode* tCase = buildAssignment( iter, vars, funs );
            iter.advance(); // move past ':'
            ExprNode* fCase = buildAssignment( iter, vars, funs );
            return new Conditional( cond, tCase, fCase );
        }
        else
        {
            return cond;
        }
    }
    else
    {
        return left;
    }
}

// BuildSum
// Builds an ExprNode subtree of a pair of other sum subtrees
//  integers, or products.
ExprNode* buildSum( ListIterator &iter, VarTree &vars, FunctionDef &funs )
{
    ExprNode* left = buildProduct( iter, vars, funs );
    if (iter.tokenChar() == '+' || iter.tokenChar() == '-')
    {
        string op = iter.token().tokenText();
        iter.advance(); // move past operator
        ExprNode* right = buildSum( iter, vars, funs );
        return new Operation( left, op, right );
    }
    else
    {
        return left;
    }
}

// BuildProduct
// Builds an ExprNode subtree of either a single value or a product
ExprNode* buildProduct( ListIterator &iter, VarTree &vars, FunctionDef &funs )
{
    ExprNode* left; // the left branch of the product tree
    if (iter.currentIsInteger())
    {
        left = new Value( iter.integerValue() );
        iter.advance();
    }
    else if (iter.tokenChar() == '(')
    {
        left = buildParentheses( iter, vars, funs );
        iter.advance();
    }
    else if (iter.tokenChar() == '-') // there is a negative number
    {
        iter.advance();
        left = new Operation( new Value(-1), "*", buildProduct(iter, vars, funs) );
    }
    else // it has to be a var or a function
    {
        left = buildFunctionOrVariable( iter, vars, funs );
    }
    // if the operator is *, /, %, build a subtree with its operands
    if (iter.tokenChar() == '*' || iter.tokenChar() == '/' || iter.tokenChar() == '%')
    {
        string op = iter.token().tokenText();
        iter.advance(); // move past operator
        ExprNode* right = buildProduct( iter, vars, funs );
        return new Operation( left, op, right );
    }
    else // otherwise, the subtree consists of a single factor
    {
        return left;
    }
}

// Builds a parenthetical expression subtree node
ExprNode* buildParentheses( ListIterator &iter, VarTree &vars, FunctionDef &funs )
{
    ExprNode* parenRoot; // the subtree's root node
    TokenList parenExpr = TokenList();
    int numParens = 1;
    // build the parenthetical expression's tokenlist
    while (numParens > 0)
    {
        iter.advance();
        if (iter.tokenChar() == '(')
            numParens++;
        else if (iter.tokenChar() == ')')
            numParens--;
        parenExpr.push_back( iter.token() );
    }
    ListIterator pIter = parenExpr.begin();
    return buildAssignment( pIter, vars, funs );
}

// Either returns a function node, NULL for a definition, or a variable
//   node based on the current situation.
ExprNode* buildFunctionOrVariable( ListIterator &iter, VarTree &vars, FunctionDef &funs )
{
    if (iter.token().tokenText() == "deffn")
    {
        FunDef fun; // create a new function def
        fun.locals = new VarTree();
    	iter.advance();
    	fun.name = iter.token().tokenText();
        iter.advance(); // move past function name
    	iter.advance(); // move past '('
        for (int i = 0; iter.tokenChar() != ')'; i++)
    	{
    	    fun.locals->lookup( iter.token().tokenText() );
            fun.parameter[i] = iter.token().tokenText();
    	    iter.advance(); // move past parameter var
            if (iter.token().tokenText() == ",")
                iter.advance(); // move past comma, when present
    	}
    	iter.advance(); // move past ')'
    	iter.advance(); // move past '='
    	fun.functionBody = buildAssignment( iter, *fun.locals, funs );
    	funs[fun.name] = fun; // add to map
    	return NULL;
    }
    else {
        string name = iter.token().tokenText();
        iter.advance();
        if (iter.tokenChar() == '(')
        {
            FunDef fn;
            fn = funs[name];
            iter.advance();
            ExprNode* params[10];
            int i;
            for (i = 0; iter.tokenChar() != ')'; i++)
            {
                params[i] = buildAssignment( iter, vars, funs );
                if (iter.tokenChar() == ',') // move past a comma if present
                    iter.advance();
            }
            return new Function( name, params, i );
        }
        else
        {
            return new Variable( name );
        }
    }
}
