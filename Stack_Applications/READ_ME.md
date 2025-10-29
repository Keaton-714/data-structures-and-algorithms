Stack-Based Algorithms Project
A C++ implementation of a stack data structure using arrays, with applications in:

Converting infix expressions to postfix notation (Shunting Yard algorithm)
Evaluating postfix expressions
Checking balanced parentheses/brackets/braces
The project includes unit tests via input files that verify if correct and output OK || ERROR for each test case.

Files:

stack.hpp - Header file defining the Stack<T> template class with methods: push, pop, peek, size, display.
stack.cpp - Implementation of the Stack<T> class methods. Explicitly instantiates Stack<char> and Stack<int>.
infix2postfix.cpp - Program to convert infix expressions to postfix using the stack. Reads from input_infix2post.txt and validates against expected outputs.
postfixEval.cpp - Program to evaluate postfix expressions (single-digit operands only). Reads from input_postfixEval.txt and validates results.
balancing.cpp - Program to check if parentheses, brackets, and braces are balanced in a string. Reads from input_balanced.txt and validates yes/no.
input_infix2postfix.txt - Test cases for infix-to-postfix conversion (format: expected_postfix infix_expression).
input_postfixEval.txt - Test cases for postfix evaluation (format: expected_result postfix_expression).
input_balanced.txt - Test cases for balancing check (format: yes/no expression)

Example Compilation (using g++):

g++ infix2postfix.cpp stack.cpp -o infix2postfix
g++ postfixEval.cpp stack.cpp -o postfixEval
g++ balancing.cpp stack.cpp -o balancing

Running the Programs:
Place the input files in the same directory as the executables.

./infix2postfix   # Outputs debug and OK/ERROR for each line in input_infix2post.txt
./postfixEval     # Similar for postfixEval
./balancing       # Similar for balancing
