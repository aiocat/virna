#include <iostream>
#include <stack>
#include <fstream>
std::stack<int> _stack;int _temp_one, _temp_two;std::stack<std::string> _string_stack;std::string _string_temp_one, _string_temp_two;std::ifstream _text_file;std::ofstream _otext_file;inline int __over(){int temp=0;temp=_stack.top();_stack.pop();_stack.push(_stack.top());_stack.push(temp);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_one);_stack.push(_temp_two);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};inline int factorial(){_stack.push(_stack.top());_stack.push(_stack.top());int temp=0;temp=_stack.top();_stack.pop();_stack.push(temp);_stack.push(3);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two<_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_stack.pop();_stack.pop();_stack.push(temp);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};while(_stack.top()!=0){_stack.push(1);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two-_temp_one);_stack.push(temp);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two*_temp_one);temp=_stack.top();_stack.pop();_stack.push(1);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two-_temp_one);_stack.push(_stack.top());_stack.push(_stack.top());_stack.push(2);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two==_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){break;};};_stack.pop();_stack.pop();_stack.push(temp);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};inline int sqrt(){_stack.push(_stack.top());_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two*_temp_one);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};inline int cbrt(){_stack.push(_stack.top());_stack.push(_stack.top());_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two*_temp_one);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two*_temp_one);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};inline int abs(){_stack.push(_stack.top());_stack.push(0);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two>=_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};_stack.push(0);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_one);_stack.push(_temp_two);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two-_temp_one);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};inline int conv(){_stack.push(0);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_one);_stack.push(_temp_two);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two-_temp_one);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};inline int max(){_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_one);_stack.push(_temp_two);_temp_one=__over();if(_temp_one!=0)return _temp_one;_temp_one=__over();if(_temp_one!=0)return _temp_one;_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two>_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_stack.pop();_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;}else{_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_one);_stack.push(_temp_two);_stack.pop();_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};};inline int min(){_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_one);_stack.push(_temp_two);_temp_one=__over();if(_temp_one!=0)return _temp_one;_temp_one=__over();if(_temp_one!=0)return _temp_one;_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two<_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_stack.pop();_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;}else{_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_one);_stack.push(_temp_two);_stack.pop();_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};};inline int ask(){_string_stack.push("Enter a Number: ");_string_temp_one=_string_stack.top();_string_stack.pop();std::cout<<_string_temp_one;std::cin>>_temp_one;_stack.push(_temp_one);_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};int main(){_temp_one=ask();if(_temp_one!=0)return _temp_one;_temp_one=cbrt();if(_temp_one!=0)return _temp_one;_temp_one=_stack.top();_stack.pop();std::cout<<_temp_one;_stack.push(10);_temp_one=_stack.top();_stack.pop();std::cout<<(char)_temp_one;_stack.push(5);_temp_one=_stack.top();_stack.pop();_stack.push(-_temp_one);_temp_one=abs();if(_temp_one!=0)return _temp_one;_temp_one=_stack.top();_stack.pop();std::cout<<_temp_one;_stack.push(10);_temp_one=_stack.top();_stack.pop();std::cout<<(char)_temp_one;_stack.push(8);_stack.push(2);_temp_one=max();if(_temp_one!=0)return _temp_one;_temp_one=_stack.top();_stack.pop();std::cout<<_temp_one;_stack.push(10);_temp_one=_stack.top();_stack.pop();std::cout<<(char)_temp_one;_stack.push(3);_stack.push(10);_temp_one=min();if(_temp_one!=0)return _temp_one;_temp_one=_stack.top();_stack.pop();std::cout<<_temp_one;_stack.push(0);_temp_one=_stack.top();_stack.pop();return _temp_one;};
