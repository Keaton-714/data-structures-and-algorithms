#include "stack.hpp"
#include <map>

using namespace std;

bool balance(string s)
{
  Stack<char> stack; // empty stack to push open braces in
  map<char, char> match = 
  {
    {')', '('},
    {']', '['},
    {'}', '{'}
  }; // to easily check if the braces match

  for(int i=0; i<s.length(); ++i) 
  {
    if (s[i] == '(' || s[i] == '{' || s[i] == '[')
    {
      stack.push(s[i]); // pushing if open
    }
    else if (s[i] == ')' || s[i] == '}' || s[i] == ']') // if closed 
    {
      if (stack.size() == 0) return false; // no bueno
      if (stack.peek() != match[s[i]]) return false; // checking if it has a mate
      stack.pop(); // pop since the mate was found 
    }
    else 
    {
      continue; // skip over letters, numbers, and operators
    }
  }
  return stack.size() == 0; // return true if stack is empty
}

int main()
{
  freopen("input_balanced.txt", "r", stdin);
  string s,r;
  int line_counter = 1;
  bool solution;
  bool isBalanced;
  while(cin >> r)
  {
    cin>>s;
    if(r[0] == 'Y' || r[0] == 'y')
    {
      solution = true;
    }
    else
    {
      solution = false;
    }
    // The input file is in the format "expected_solution expression"
    // so variable solution tells you whether 'expression' is balanced or not
    // checking if you stored in isBalanced the correct value
    isBalanced = balance(s);
    if(isBalanced == solution)
    {
      cout << "line " << line_counter << ": OK [" << solution << " " << isBalanced << "]" << endl;
    }
    else
    {
      cout << "line " << line_counter << ": ERROR [" << solution << " " << isBalanced << "]" << endl;
    }
    line_counter++;
  }

return 0;
}
