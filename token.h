// Token Header file
// This is for the beginning of an object-oriented string tokenizer
// to be used for arithmetic expressions.    The tokenizer is an
// object that returns a linked list of object tokens, which are these.

// Since lots of files want to know what a token is, there is the
// danger of redeclaration, which these next couple lines will neutralize.
// (There is an #endif at the bottom as well)
#ifndef TOKEN
#define TOKEN

// Provides some helpful functionality for understanding tokens
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctype.h>
using namespace std;
 
// Here is a definition of the token itself:
class Token {
    //  All the data members are private to keep them protected.
    private:
	bool    isInt;		// to identify the token type later
	int	value;		// value for an integer token
	string	text;		// character for an operator token

    //  All of the methods here are public (which is not always the case)
    //  First, a couple to initialize a new token, either operator or integer
    public:			// and some constructors to initialize
	Token(char c)		// single character
	{
	    text = "" ;   
	    text += c;
	    isInt = false;
	    value = 0;		// initialize unused value
	}
	Token(string s)		// full string
	{			
	    text =  s;     
	    isInt = false;
	    value = 0;		// initialize unused value
	}
	Token(int i)		// integer value
	{		
	    value = i;
	    isInt = true;
	    text = "";		// initialize unused value
	}

	Token()			// default constructor
	{
	    value = 0;
	    text = "";
	    isInt = false;
	}
	//  Here are several accessor methods used to describe
	//  the token, making visible the hidden private members.
	//  No changes are permitted to this object -- only queries.
	//
	//  Placing these within the class definition allows for
	//  inline expansion at the function call point, to save
	//  the need for call and return.  In-line is only suitable
	//  for very short functions (like these and constructors).

	bool isNull() const
	{
	    return !isInt && text=="";
	}

	bool isInteger() const
	{
	    return isInt;
	}

	int integerValue() const
	{
	    return value;
	}
	
	string tokenText() const
	{
	    return text;
	}

	char tokenChar() const
	{
	    return text[0];
	}

	//   And a function that  will be postponed to an
	//   implementation file.

	friend ostream& operator <<( ostream& stream, Token &t);
};

// And of the conditional compilation
#endif
