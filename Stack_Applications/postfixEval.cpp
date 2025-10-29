#include "stack.hpp"

using namespace std;

int main()
{
  freopen("input_postfixEval.txt", "r", stdin);
  string s;
  int solution;
  int line_counter = 0;
  while(cin>>solution)
  {
    cin>>s;
    Stack<int> stack;
    
    // The input file is in the format "expected_solution postfix_expression"

    // We assume that all operands in the input are one digit (so they range from 0 to 9)
    // NOTE: you need to convert each digital from 'char' to 'int' before you do the calculation ***
    int left;
    int right;

    for (int i = 0; i < s.length(); ++i)
    {
      if (s[i] != '+' && s[i] != '-' && s[i] != '/' && s[i] != '*')
      {
        int x = s[i] - '0'; // makes into int 
        stack.push(x); // pushing operands into stack
      }
      else if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*')
      {
        right = stack.pop();
        left = stack.pop();
        char op = s[i];
        int num;

        switch (op)
        {
          case '+':
          {
              num = left + right;
              break;
          }
          case '-':
          {
            num = left - right;
            break;
          }
          case '/':
          {
            num = left / right;
            break;
          }
          case '*':
          {
            num = left * right;
            break;
          }
          default:
          {
            cout << "Invalid argument" << endl;
          }
        }
        stack.push(num); // putting the result back into the stack
      }
    }

    // Checking whether the value you calculated is correct ...
    int value = stack.pop();

    if(solution == value)
    {
      cout << "line " << line_counter << ": OK [" << solution << " " << value << "]" << endl;
    }
    else
    {
      cout << "line " << line_counter << ": ERROR [" << solution << " " << value << "]" << endl;
    }
    line_counter++;
  }
}
