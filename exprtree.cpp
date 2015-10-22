// Expression Tree Implementation File
// These functions manage an expression tree that describes
// arithmetic expressions using integer variables and values.
// Some functions construct a tree from a character string that
// represents the expression, and then the tree can be traversed
// and evaluated.
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;
#include "exprtree.h"
#include "tokenlist.h"


// Outputting any tree node will simply output its string version
ostream& operator<<( ostream &stream, const ExprNode &e )
{
    return stream << e.toString();
}

// A Value is just an integer value -- easy to evaluate
// Unfortunately, the string class does not have a constructor for it
string Value::toString() const
{
    ostringstream convert;	// output string stream
    convert << value;		// 'output' into the stream
    return convert.str();	// and extract its string equivalent
}

int Value::evaluate( VarTree &v, FunctionDef &f ) const
{
    return value;
}

//  A variable is just an alphabetic string -- easy to display
//  TO evaluate, would need to look it up in the data structure
string Variable::toString() const
{
    return name;
}

int Variable::evaluate( VarTree &v, FunctionDef &f ) const
{
    return v.lookup( name );
}

string Operation::toString() const
{
    return oper;
}

int Operation::evaluate( VarTree &v, FunctionDef &f ) const
{
    int result;
    if (oper == "+")
        result = left->evaluate( v, f ) + right->evaluate( v, f );
    else if (oper == "-")
        result = left->evaluate( v, f ) - right->evaluate( v, f );
    else if (oper == "*")
        result = left->evaluate( v, f ) * right->evaluate( v, f );
    else if (oper == "/")
        result = left->evaluate( v, f ) / right->evaluate( v, f );
    else if (oper == "%%")
        result = left->evaluate( v, f ) % right->evaluate( v, f );
    else if (oper == "<")
        result = left->evaluate( v, f ) < right->evaluate( v, f );
    else if (oper == ">")
        result = left->evaluate( v, f ) > right->evaluate( v, f );
    else if (oper == "<=")
        result = left->evaluate( v, f ) <= right->evaluate( v, f );
    else if (oper == ">=")
        result = left->evaluate( v, f ) >= right->evaluate( v, f );
    else if (oper == "==")
        result = left->evaluate( v, f ) == right->evaluate( v, f );
    else if (oper == "=")
    {
        v.assign( left->toString(), right->evaluate(v, f) );
        result = left->evaluate( v, f );
    }
    else
        result = left->evaluate( v, f ) != right->evaluate( v, f );
    return result;
}

string Conditional::toString() const
{
    return test->toString();
}

int Conditional::evaluate( VarTree &v, FunctionDef &f  ) const
{
    bool testResult = test->evaluate( v, f );
    if (testResult)
        return trueCase->evaluate( v, f );
    else
        return falseCase->evaluate( v, f );
}

string Function::toString() const
{
    return name;
}

int Function::evaluate( VarTree &v, FunctionDef &f ) const
{
    FunDef fn = f[name];
    fn.locals = new VarTree();
    for (int i = 0; i < paramSize; i++)
        fn.locals->assign( fn.parameter[i], param[i]->evaluate(v, f) );
    return fn.functionBody->evaluate( *fn.locals, f );
}
