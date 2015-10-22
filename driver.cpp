#include <iostream>
using namespace std;
#include "evaluate.h"

int main()
{
    char userInput[80];
    VarTree vars;		// initially empty tree
    FunctionDef funs;
    cout << "Write a mathematical expression with operators and parens:" << endl;
    cout << "2 * (3 + 2) = " << evaluate("2 * (3 + 2)", vars, funs);
    cout << endl << "Define variables with an assignment operator:" << endl;
    cout << "x = 5 -> " << evaluate("x=5", vars, funs) << endl;
    cout << "x * 2 = " << evaluate("x*2", vars, funs) << endl;  
    cout << endl << "Try one:  ";
    cin.getline(userInput,80);
    cout << userInput << " = " << evaluate(userInput, vars, funs) << endl;
    while(true) { // let 'em keep going
        cout << endl << "Try another:  ";
        cin.getline(userInput,80);
        cout << userInput << " = " << evaluate(userInput, vars, funs) << endl;
    }
}
