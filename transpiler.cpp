#include <algorithm>

#include "./lexer.cpp"

class Transpiler
{
public:
    std::vector<Token> tokens;
    std::string source;
    std::vector<std::string> includes;
    std::vector<std::string> functions;
    std::vector<std::string> variables;

    void run();
};

void Transpiler::run()
{
    includes.push_back("iostream");
    includes.push_back("stack");

    source = "std::stack<int> _stack;int _temp_one, _temp_two;std::stack<std::string> _string_stack;std::string _string_temp_one, _string_temp_two;";

    for (int index = 0; index < tokens.size(); index++)
    {
        Token token = tokens[index];

        switch (token.key)
        {
        case Commands::Number:
            source += ("_stack.push(" + token.value + ");");
            break;
        case Commands::Add:
            source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two+_temp_one);";
            break;
        case Commands::Sub:
            source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two-_temp_one);";
            break;
        case Commands::Dimo:
            source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push((int)_temp_two/_temp_one);_stack.push(_temp_two%%_temp_one);";
            break;
        case Commands::Mul:
            source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two*_temp_one);";
            break;
        case Commands::Ret:
            source += "_temp_one=_stack.top();_stack.pop();return _temp_one;";
            break;
        case Commands::End:
            source += "};";
            break;
        case Commands::Put:
            source += "_temp_one=_stack.top();_stack.pop();std::cout<<_temp_one;";
            break;
        case Commands::Compare:
            source += ("_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_temp_two" + token.value + "_temp_one ? _stack.push(1) : _stack.push(0);");
            break;
        case Commands::If:
            source += "_temp_one=_stack.top();_stack.pop();if(_temp_one==1){";
            break;
        case Commands::While:
            source += "while(_stack.top()!=0){";
            break;
        case Commands::Break:
            source += "break;";
            break;
        case Commands::Skip:
            source += "continue;";
            break;
        case Commands::Dup:
            source += "_stack.push(_stack.top());";
            break;
        case Commands::Swap:
            source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_one);_stack.push(_temp_two);";
            break;
        case Commands::Pop:
            source += "_stack.pop();";
            break;
        case Commands::Else:
            source += "}else{";
            break;
        case Commands::String:
            source += ("_string_stack.push(\"" + token.value + "\");");
            break;
        case Commands::Adds:
            source += "_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_two+_string_temp_one);";
            break;
        case Commands::Puts:
            source += "_string_temp_one=_string_stack.top();_string_stack.pop();std::cout<<_string_temp_one;";
            break;
        case Commands::Dups:
            source += "_string_stack.push(_string_stack.top());";
            break;
        case Commands::Swaps:
            source += "_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_string_stack.push(_string_temp_one);_string_stack.push(_string_temp_two);";
            break;
        case Commands::Pops:
            source += "_string_stack.pop();";
            break;
        case Commands::Eqs:
            source += "_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();if(_string_temp_one==_string_temp_two){_stack.push(1);}else{_stack.push(0);};";
            break;
        case Commands::Putc:
            source += "_temp_one=_stack.top();_stack.pop();std::cout<<(char)_temp_one;";
            break;
        case Commands::Lens:
            source += "_string_temp_one=_string_stack.top();_string_stack.pop();_stack.push(_string_temp_one.length());";
            break;
        case Commands::Revs:
            if (std::find(variables.begin(), variables.end(), token.value) == variables.end())
                includes.push_back("algorithm");
                
            source += "_string_temp_one=_string_stack.top();_string_stack.pop();std::reverse(_string_temp_one.begin(),_string_temp_one.end());_string_stack.push(_string_temp_one);";
            break;
        case Commands::Trns:
            source += "_string_temp_one=_string_stack.top();_string_stack.pop();_stack.push(0);for(int _i=0;_i<_string_temp_one.length();_i++){_stack.push((int)_string_temp_one[_i]);};";
            break;
        case Commands::Unknown:
            if (std::find(functions.begin(), functions.end(), token.value) != functions.end())
                source += ("_temp_one=" + token.value + "();if(_temp_one!=0)return _temp_one;");
            else if (tokens[index - 1].key == Commands::In)
            {
                source += ("int " + token.value + "(){");
                functions.push_back(token.value);
            }

            if (std::find(variables.begin(), variables.end(), token.value) != variables.end())
                if (tokens[index - 1].key == Commands::Set)
                    source += (token.value + "=_stack.top();_stack.pop();");
                else
                    source += ("_stack.push(" + token.value + ");");
            else if (tokens[index - 1].key == Commands::Let)
            {
                source += ("int " + token.value + "=0;");
                variables.push_back(token.value);
            }
            break;
        default:
            break;
        }
    }

    std::string upperCode = std::string();

    for (int i = 0; i < includes.size(); i++)
    {
        upperCode += ("#include <" + includes[i] + ">\n");
    }

    source = upperCode + source;
}