// Token List Implementation file
//
// This tokenizer will scan a character string representing
// an expression, and will return a list of tokens.
// --- only integers and operators are supported (no names)

// The standard C library has some useful functions for us
#include <string.h>
#include <ctype.h>

// And to get the definition of a token:
#include "tokenlist.h"

bool isoperator( char );

// First, a helper function that identifies a single token
// from the character string.

// getToken:
// Identifies the token found at the given character position
// Parameters:
// 	str	(modified char pointer)		position to scan
//	token	(output Token)			the found token
// The character pointer is advanced past the scanned token.
// If no more non-space data is found, a null pointer is returned.
void getToken( const char *&str, Token &token  )
{
    string temp;			// temporary text to work with

    while (*str == ' ')			// skip any spaces
	   str++;

    if (*str == 0)			// at end of string
    {
    	token = Token();
    }
    else if (isdigit(*str))
    {
    	token = Token(atoi(str));		// convert to integer
    	while (isdigit(*str))
    	    str++;			// scan past the intie
    }
    else if (isalpha(*str))
    {
        string varName = "";
        do {
            varName += *str;
            str++;
        } while(isalpha(*str));
        token = Token(varName);
    }
    else //its an operator
    {
        temp = *str;
        str++;				    // move past the operator
        if (*str == '=')        // check for an instance of <=, >=, ==, or !=
        {
            temp += *str;
            str++; // move past '='
        }
        token = Token(temp);
    }
}

// TokenList constructor
// converts a character string into a list of tokens
// Parameter:
// 	expr	(input char pointer)	// string to examine
// Pre-condition:  str may not be a null pointer
//     and is assumed to actually point at a valid expression.
TokenList::TokenList( const char expr[] )
{
    head = NULL;			// clear these here too
    tail = NULL;
    Token current;
    const char *str = expr;		   // a copy of the pointer to work with
    getToken( str, current );	  // get the first token
    while (!current.isNull())
    {
        push_back( current );
        getToken( str, current );	// get another token
    }
}

//  output operation
//  Display all of the tokens in the list
ostream& operator<<( ostream &stream, TokenList &t )
{
    for (ListIterator iter = t.begin(); iter != t.end(); iter.advance())
    {
	stream << iter.token() << ",";
    }
    return stream;
}

//  Creates an iterator to refer to the beginning of the list
ListIterator TokenList::begin()
{
    return ListIterator( this, head );
}

//  Creates an iterator to refer after the end of the list
//  This list is simple:  it ends with NULL
ListIterator TokenList::end()
{
    return ListIterator( this, NULL );
}

//  Add a new element to the back of the list
//  Parameter:
//       t	(input Token)	the new item to add
void TokenList::push_back( Token t )
{
    ListElement *le = new ListElement;
    le->token = t;
    le->next = NULL;
    if (this->empty()) // if empty, both the head and tail are the same
    {
        head = le;
        tail = le;
    }
    else
    {
        tail->next = le;
        tail = le;
    }
}

//  Add a new element to the front of the list
//  Parameter:
//       t	(input Token)	the new item to add
void TokenList::push_front( Token t )
{
    ListElement *le = new ListElement;
    le->token = t;
    if (this->empty()) // if empty, both the head and tail are the same
    {
        head = le;
        tail = le;
    }
    else
    {
        le->next = head;
        head = le;
    }
}

// Remove and return the element at the front of the list
// pre-condition: list isn't empty
Token TokenList::pop_front()
{
    Token popped = head->token;
    if (head->next != NULL) // there are 2+ items in the list
        head = head->next;
    else // otherwise, this is the only element in the list
        head = NULL;
    return popped;
}

bool isoperator( char c )
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')');
}
