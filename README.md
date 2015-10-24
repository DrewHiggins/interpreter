# C++ Mathematical Interpreter
This program was the sole project assigned in my CMPSC122 class at Penn State. 
It was assigned in 6 parts over the course of the Spring 2015 semester with each
assignment building on the last and adding in new data structures and algorithms as 
we learned them (including BSTs and linked lists). Some of the code was provided,
such as the implementation of a few data structures, but the majority of the business
logic had to be solved by the student.

## Functionality
The program serves as a mathematical expression interpreter. If you give it an expression
such as `(2+3)/3`, it will spit out `2`.

It also supports variables, so typing `x = 2` will store `x` in memory and allow 
you to use it in future calculations, like so:

    x * 5 = 10

Lastly, the program supports simple funciton definitions, like so:

    deffn add(x,y) = x + y
    add(3,2) = 6
