#include <algorithm>

#include "./lexer.cpp"

class Transpiler
{
public:
    bool allowInclude;
    std::vector<Token> tokens;
    std::string source;
    std::vector<std::string> includes;
    std::vector<std::string> functions;
    std::vector<std::string> int_variables;
    std::vector<std::string> str_variables;

    void run();
};

void Transpiler::run()
{
    if (allowInclude)
    {
        includes.push_back("iostream");
        includes.push_back("stack");
        includes.push_back("fstream");

        source = "std::stack<int> _stack;int _temp_one, _temp_two;std::stack<std::string> _string_stack;std::string _string_temp_one, _string_temp_two;std::ifstream _text_file;std::ofstream _otext_file;";
    }

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
        case Commands::Appendc:
            source += "_temp_one=_stack.top();_stack.pop();_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_one+=(char)_temp_one;_string_stack.push(_string_temp_one);";
            break;
        case Commands::Lens:
            source += "_string_temp_one=_string_stack.top();_string_stack.pop();_stack.push(_string_temp_one.length());";
            break;
        case Commands::Revs:
            if (std::find(includes.begin(), includes.end(), "algorithm") == includes.end())
                includes.push_back("algorithm");

            source += "_string_temp_one=_string_stack.top();_string_stack.pop();std::reverse(_string_temp_one.begin(),_string_temp_one.end());_string_stack.push(_string_temp_one);";
            break;
        case Commands::Trns:
            source += "_string_temp_one=_string_stack.top();_string_stack.pop();_stack.push(0);for(int _i=0;_i<_string_temp_one.length();_i++){_stack.push((int)_string_temp_one[_i]);};";
            break;
        case Commands::Get:
            source += "std::cin>>_temp_one;_stack.push(_temp_one);";
            break;
        case Commands::Gets:
            source += "std::cin>>_string_temp_one;_string_stack.push(_string_temp_one);";
            break;
        case Commands::Read:
            source += "_string_temp_one=_string_stack.top();_string_stack.pop();_text_file.open(_string_temp_one);if(!_text_file){_stack.push(0);};_text_file.seekg(0,std::ios::end);_string_temp_two=std::string();_string_temp_two.reserve(_text_file.tellg());_text_file.seekg(0,std::ios::beg);_string_temp_two.assign((std::istreambuf_iterator<char>(_text_file)),std::istreambuf_iterator<char>());_text_file.close();_string_stack.push(_string_temp_two);_stack.push(1);";
            break;
        case Commands::Write:
            source += "_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_otext_file.open(_string_temp_one);if(!_otext_file){_stack.push(0);};_otext_file<<_string_temp_two;_otext_file.close();_stack.push(1);";
            break;
        case Commands::Shell:
            if (std::find(includes.begin(), includes.end(), "stdlib.h") == includes.end())
                includes.push_back("stdlib.h");

            source += "_string_temp_one=_string_stack.top();_string_stack.pop();_stack.push(system(_string_temp_one.c_str()));";
            break;
        case Commands::Unknown:
            if (std::find(functions.begin(), functions.end(), token.value) != functions.end())
            {
                source += ("_temp_one=" + token.value + "();if(_temp_one!=0)return _temp_one;");
                break;
            }
            else if (tokens[index - 1].key == Commands::In)
            {
                if (tokens[index + 1].key == Commands::Inline)
                    source += ("inline int " + token.value + "(){");
                else
                    source += ("int " + token.value + "(){");

                functions.push_back(token.value);
                break;
            }

            if (std::find(int_variables.begin(), int_variables.end(), token.value) != int_variables.end())
            {
                if (tokens[index - 1].key == Commands::Set)
                    source += (token.value + "=_stack.top();_stack.pop();");
                else if (tokens[index - 1].key == Commands::Let)
                    source += ("int " + token.value + "=0;");
                else
                    source += ("_stack.push(" + token.value + ");");

                break;
            }
            else if (tokens[index - 1].key == Commands::Let)
            {
                source += ("int " + token.value + "=0;");
                int_variables.push_back(token.value);
                break;
            }

            if (std::find(str_variables.begin(), str_variables.end(), token.value) != str_variables.end())
            {
                if (tokens[index - 1].key == Commands::Sets)
                    source += (token.value + "=_string_stack.top();_string_stack.pop();");
                else if (tokens[index - 1].key == Commands::Lets)
                    source += ("std::string " + token.value + "=std::string();");
                else
                    source += ("_string_stack.push(" + token.value + ");");

                break;
            }
            else if (tokens[index - 1].key == Commands::Lets)
            {
                source += ("std::string " + token.value + "=std::string();");
                str_variables.push_back(token.value);
                break;
            }

            std::cerr << "[L" << token.line << "]: Unknown token error\n";
            exit(1);

        case Commands::String:
            if (tokens[index - 1].key == Commands::Import)
            {
                std::string fileContent;
                std::ifstream textFile(token.value);

                if (!textFile)
                {
                    std::cerr << "Not a valid file path";
                    break;
                }

                textFile.seekg(0, std::ios::end);
                fileContent.reserve(textFile.tellg());
                textFile.seekg(0, std::ios::beg);

                fileContent.assign((std::istreambuf_iterator<char>(textFile)), std::istreambuf_iterator<char>());
                textFile.close();

                Lexer lexer;
                lexer.line = 1;
                lexer.raw = fileContent;

                lexer.run();

                Transpiler transpiler;
                transpiler.tokens = lexer.tokens;
                transpiler.allowInclude = false;

                transpiler.run();
                source += transpiler.source;

                for (int i = 0; i < transpiler.includes.size(); i++)
                    if (std::find(includes.begin(), includes.end(), transpiler.includes[i]) == includes.end())
                        includes.push_back(transpiler.includes[i]);

                for (int i = 0; i < transpiler.functions.size(); i++)
                    functions.push_back(transpiler.functions[i]);

                for (int i = 0; i < transpiler.int_variables.size(); i++)
                    int_variables.push_back(transpiler.int_variables[i]);

                for (int i = 0; i < transpiler.str_variables.size(); i++)
                    str_variables.push_back(transpiler.str_variables[i]);
            }
            else
            {
                source += ("_string_stack.push(\"" + token.value + "\");");
                break;
            }
        default:
            break;
        }
    }

    if (allowInclude)
    {
        std::string upperCode = std::string();
        for (int i = 0; i < includes.size(); i++)
            upperCode += ("#include <" + includes[i] + ">\n");

        source = upperCode + source;
    }
}