#include <iostream>
#include <stack>
#include <fstream>
#include <algorithm>
std::stack<int> _stack;int _temp_one, _temp_two;std::stack<std::string> _string_stack;std::string _string_temp_one, _string_temp_two;std::ifstream _text_file;std::ofstream _otext_file;int main(){_string_stack.push("File to read (without .bf extension): ");_string_temp_one=_string_stack.top();_string_stack.pop();std::cout<<_string_temp_one;std::cin>>_string_temp_one;_string_stack.push(_string_temp_one);_string_stack.push(_string_stack.top());_string_stack.push(".bf");_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);_string_temp_one=_string_stack.top();_string_stack.pop();_text_file.open(_string_temp_one);if(!_text_file){_stack.push(0);};_text_file.seekg(0,std::ios::end);_string_temp_two=std::string();_string_temp_two.reserve(_text_file.tellg());_text_file.seekg(0,std::ios::beg);_string_temp_two.assign((std::istreambuf_iterator<char>(_text_file)),std::istreambuf_iterator<char>());_text_file.close();_string_stack.push(_string_temp_two);_stack.push(1);_string_temp_one=_string_stack.top();_string_stack.pop();std::reverse(_string_temp_one.begin(),_string_temp_one.end());_string_stack.push(_string_temp_one);_string_temp_one=_string_stack.top();_string_stack.pop();_stack.push(0);for(int _i=0;_i<_string_temp_one.length();_i++){_stack.push((int)_string_temp_one[_i]);};_string_stack.push("#include <stdio.h>\nchar array[30000]={0}; char *ptr = array;\nint main(){");while(_stack.top()!=0){_stack.push(_stack.top());_stack.push(43);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two==_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_string_stack.push("++*ptr;");_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);};_stack.push(_stack.top());_stack.push(45);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two==_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_string_stack.push("--*ptr;");_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);};_stack.push(_stack.top());_stack.push(62);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two==_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_string_stack.push("++ptr;");_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);};_stack.push(_stack.top());_stack.push(60);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two==_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_string_stack.push("--ptr;");_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);};_stack.push(_stack.top());_stack.push(46);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two==_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_string_stack.push("putchar(*ptr);");_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);};_stack.push(_stack.top());_stack.push(44);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two==_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_string_stack.push("*ptr=getchar();");_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);};_stack.push(_stack.top());_stack.push(91);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two==_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_string_stack.push("while(*ptr){");_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);};_stack.push(_stack.top());_stack.push(93);_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two==_temp_one ? _stack.push(1) : _stack.push(0);_temp_one=_stack.top();_stack.pop();if(_temp_one==1){_string_stack.push("};");_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);};_stack.pop();};_string_stack.push("};");_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_one);_string_stack.push(_string_temp_two);_string_stack.push(".c");_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_otext_file.open(_string_temp_one);if(!_otext_file){_stack.push(0);};_otext_file<<_string_temp_two;_otext_file.close();_stack.push(1);};
