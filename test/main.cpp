#include <iostream>
#include <stack>
#include <algorithm>
std::stack<int> _stack;int _temp_one, _temp_two;std::stack<std::string> _string_stack;std::string _string_temp_one, _string_temp_two;int main(){_string_stack.push("Hello, World!");_string_temp_one=_string_stack.top();_string_stack.pop();std::reverse(_string_temp_one.begin(),_string_temp_one.end());_string_stack.push(_string_temp_one);_string_temp_one=_string_stack.top();_string_stack.pop();_stack.push(0);for(int _i=0;_i<_string_temp_one.length();_i++){_stack.push((int)_string_temp_one[_i]);};while(_stack.top()!=0){_temp_one=_stack.top();_stack.pop();std::cout<<(char)_temp_one;};};
