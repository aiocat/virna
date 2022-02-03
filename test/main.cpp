#include <iostream>
#include <stack>
std::stack<int> _stack;int _temp_one, _temp_two;int main(){_stack.push(50);_stack.push(10);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two==_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();std::cout<<_temp_one;};
