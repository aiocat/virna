#include <iostream>
#include <stack>
#include <algorithm>
#include <fstream>
std::stack<int> _stack;int _temp_one, _temp_two;std::stack<std::string> _string_stack;std::string _string_temp_one, _string_temp_two;std::ifstream _text_file;std::ofstream _otext_file;inline int factorial(){_stack.push(_stack.top());_stack.push(_stack.top());int temp=0;temp=_stack.top();_stack.pop();_stack.push(temp);_stack.push(3);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two<_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_stack.pop();_stack.pop();_stack.push(temp);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};while(_stack.top()!=0){_stack.push(1);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two-_temp_one);_stack.push(temp);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two*_temp_one);temp=_stack.top();_stack.pop();_stack.push(1);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two-_temp_one);_stack.push(_stack.top());_stack.push(_stack.top());_stack.push(2);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two==_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){break;};};_stack.pop();_stack.pop();_stack.push(temp);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};inline int sqrt(){_stack.push(_stack.top());_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two*_temp_one);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};inline int cube(){_stack.push(_stack.top());_stack.push(_stack.top());_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two*_temp_one);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two*_temp_one);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};inline int ask(){_string_stack.push("Enter a Number: ");_string_temp_one=_string_stack.top();_string_stack.pop();std::cout<<_string_temp_one;std::cin>>_temp_one;_stack.push(_temp_one);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};int main(){_temp_one=ask();if(_temp_one!=0)return _temp_one;_temp_one=cube();if(_temp_one!=0)return _temp_one;_temp_one=_stack.top();_stack.pop();std::cout<<_temp_one;_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};
