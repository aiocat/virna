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

    source = "std::stack<int> _stack;int _temp_one, _temp_two;";

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
        case Commands::Div:
            source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two/_temp_one);";
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
        case Commands::Dump:
            source += "_temp_one=_stack.top();_stack.pop();std::cout<<_temp_one;";
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
        upperCode += ("#include <" + includes[i] + ">\r\n");
    }

    source = upperCode + source;
}