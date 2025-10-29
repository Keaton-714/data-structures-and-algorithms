#include "stack.hpp"

using namespace std;

// Auxiliary method
// Operands are all lower case and upper case characters
bool isOperand(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Auxiliary method
int precedence(char c)
{
  if(c == '+' || c == '-'){
    return 0;
  }
  if(c == '*' || c == '/'){
    return 1;
  }
  if(c == '^'){
    return 2;
  }
  return -1;
}

int main()
{
  freopen("input_infix2postfix.txt", "r", stdin);
  string input;
  string solution;
  int line_counter = 0;
  while(cin >> solution)
  {
    cin >> input;
    Stack<char> stack;
    string result;

    cout << "DEBUG line " << line_counter << " | solution='" << solution << "' | input='" << input << "'" << endl;

     //The input file is in the format "expected_solution infix_expression", 
     //where expected_solution is the infix_expression in postfix format

    for(int i=0; i<input.length(); ++i)
    {
      // WRITE CODE HERE to store in 'result' the postfix transformation of 'input'
      char c = input[i];

      if (isOperand(c)) // find characters
      {
          result += c; 
      }
      else if (c == '(') // find open brace
      {
          stack.push(c); 
      }
      else if (c == ')') //find close brace and add each operator to the result
      {  
          while (stack.size() > 0 && stack.peek() != '(') // while stack isnt empty and not equal to open brace
          {
              result += stack.pop(); // put into result;
          }
          if (stack.size() > 0 && stack.peek() == '(') 
          {
            stack.pop(); // get rid of open brace 
          }
       }
      else // operator found
      {
        while (stack.size() > 0 && precedence(stack.peek()) >= precedence(c) && !(c == '^' && stack.peek() == '^')) 
        {
            result += stack.pop();
        }
        stack.push(c);
      }

    }
      while (stack.size() > 0)
      {
        result += stack.pop();
      }
    
    
    // Checking whether the result you got is correct
    if(solution == result)
    {
      cout << "line " << line_counter << ": OK [" << solution << " " << result << "]" << endl;
    }
    else
    {
      cout << "line " << line_counter << ": ERROR [" << solution << " " << result << "]" << endl;
    }
    line_counter++;
  }
}
