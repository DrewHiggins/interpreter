// Simple Expression Evaluation Header file
// This describes the functionality for evaluating very simple
// arithmetic expressions.  Given a string consisting of operators
// and operands, it will evaluate that expression and return its value.
//
// The expressions ma consist of the following:
// -- integer values
// -- integer variable names
// -- simple arithmetic operators ( +, -, *, /, % )
// -- the assignment operator to assign to variables
// -- matched parentheses for grouping
// -- function calls with integer arguments and return values
//
// All expressions are expected to have valid syntax.
// There is no specification on the length of any expression.

#include "vartree.h"
#include "funmap.h"

// Evaluate
// Evaluate the given expression, with the given variables defined
// New variables may be defined when this function is called
// Parameters:
//	expr	(input char array)	expression to evaluate
//	vars	(modified VarTree)	variables to work with
//	funs	(modified FunctionDef)	functions to define or call
int evaluate( const char expr[], VarTree &vars, FunctionDef &funs );
