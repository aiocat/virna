#include <algorithm>

#include "./lexer.cpp"

#ifdef _WIN32
int _OS = 1;
#else
int _OS = 0;
#endif

class Transpiler
{
public:
    bool allowInclude;
    bool quoteRuns;
    bool syscallRuns;
    bool inDefer;
    std::vector<Token> tokens;
    std::string source;
    std::vector<std::string> includes;
    std::vector<std::string> functions;

    void run();
};

void Transpiler::run()
{
    quoteRuns, syscallRuns, inDefer = false, false, false;
    std::string syscallArgs = std::string();

    if (allowInclude)
    {
        includes.push_back("iostream");
        includes.push_back("stack");
        includes.push_back("fstream");
        includes.push_back("memory");
        includes.push_back("stdint.h");

        source = "std::stack<intmax_t> _stack;intmax_t _temp_one, _temp_two, _temp_three;std::stack<std::string> _string_stack;std::string _string_temp_one, _string_temp_two;std::ifstream _text_file;std::ofstream _otext_file;\nusing defer=std::shared_ptr<void>;";
    }

    for (int index = 0; index < tokens.size(); index++)
    {
        Token token = tokens[index];

        if (!quoteRuns && !syscallRuns)
        {
            switch (token.key)
            {
            case Commands::Syscall:
                if (_OS == 1)
                {
                    std::cerr << "[L" << token.line << "]: Syscall block is not supported for windows\n";
                    exit(1);
                }
                syscallRuns = true;
                break;
            case Commands::CCode:
                source += token.value;
                break;
            case Commands::Number:
                source += ("_stack.push(" + token.value + ");");
                break;
            case Commands::Defer:
                if (!inDefer)
                    source += ("defer _temp_defer(nullptr, [](...){");
                else
                    source += ("});");

                inDefer = !inDefer;
                break;
            case Commands::Add:
                source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two+_temp_one);";
                break;
            case Commands::Sub:
                source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two-_temp_one);";
                break;
            case Commands::Dimo:
                source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push((int)_temp_two/_temp_one);_stack.push(_temp_two%_temp_one);";
                break;
            case Commands::Mod:
                source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two%_temp_one);";
                break;
            case Commands::Mul:
                source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two*_temp_one);";
                break;
            case Commands::Ret:
                source += "_temp_one=_stack.top();_stack.pop();return _temp_one;";
                break;
            case Commands::RightShift:
                source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two>>_temp_one);";
                break;
            case Commands::LeftShift:
                source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two<<_temp_one);";
                break;
            case Commands::BitwiseAnd:
                source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two & _temp_one);";
                break;
            case Commands::BitwiseOr:
                source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two | _temp_one);";
                break;
            case Commands::BitwiseXor:
                source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();_stack.push(_temp_two ^ _temp_one);";
                break;
            case Commands::BitwiseNot:
                source += "_temp_one=_stack.top();_stack.pop();_stack.push(~_temp_one);";
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
            case Commands::Repeat:
                source += "_temp_three=_stack.top();_stack.pop();for(int _t=0;_t<_temp_three;_t++){";
                break;
            case Commands::While:
                source += "while(_stack.top()!=0){";
                break;
            case Commands::Forever:
                source += "while(1){";
                break;
            case Commands::Break:
                source += "break;";
                break;
            case Commands::Try:
                source += "try{";
                break;
            case Commands::Catch:
                source += "}catch(...){";
                break;
            case Commands::Err:
                source += "throw 0;";
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
            case Commands::Iters:
                source += "_temp_one=_string_stack.top().length();for(int _vf=_temp_one-1;_vf>=0;_vf--){_string_temp_one=_string_stack.top();_string_stack.pop();_stack.push((int)_string_temp_one[_vf]);_string_temp_one.pop_back();_string_stack.push(_string_temp_one);";
                break;
            case Commands::Neg:
                source += "_temp_one=_stack.top();_stack.pop();_stack.push(-_temp_one);";
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
                source += "std::getline(std::cin,_string_temp_one);_string_stack.push(_string_temp_one);";
                break;
            case Commands::Getch:
                if (std::find(includes.begin(), includes.end(), "conio.h") == includes.end())
                    includes.push_back("conio.h");

                source += "_stack.push(getch());";
                break;
            case Commands::Rand:
                if (std::find(includes.begin(), includes.end(), "time.h") == includes.end())
                    includes.push_back("time.h");
                if (std::find(includes.begin(), includes.end(), "stdlib.h") == includes.end())
                    includes.push_back("stdlib.h");

                source += "_temp_one=_stack.top();_stack.pop();_temp_two=_stack.top();_stack.pop();srand(time(NULL));_stack.push(rand()%_temp_two+_temp_one);";
                break;
            case Commands::Sleep:
                if (_OS == 1)
                {
                    if (std::find(includes.begin(), includes.end(), "Windows.h") == includes.end())
                        includes.push_back("Windows.h");

                    source += "_temp_one=_stack.top();_stack.pop();Sleep(_temp_one*1000);";
                }
                else
                {
                    if (std::find(includes.begin(), includes.end(), "unistd.h") == includes.end())
                        includes.push_back("unistd.h");

                    source += "_temp_one=_stack.top();_stack.pop();sleep(_temp_one);";
                }
                break;
            case Commands::Readf:
                source += "_string_temp_one=_string_stack.top();_string_stack.pop();_text_file.open(_string_temp_one);if(!_text_file){_stack.push(0);};_text_file.seekg(0,std::ios::end);_string_temp_two=std::string();_string_temp_two.reserve(_text_file.tellg());_text_file.seekg(0,std::ios::beg);_string_temp_two.assign((std::istreambuf_iterator<char>(_text_file)),std::istreambuf_iterator<char>());_text_file.close();_string_stack.push(_string_temp_two);_stack.push(1);";
                break;
            case Commands::Writef:
                source += "_string_temp_one=_string_stack.top();_string_stack.pop();_string_temp_two=_string_stack.top();_string_stack.pop();_otext_file.open(_string_temp_one);if(!_otext_file){_stack.push(0);};_otext_file<<_string_temp_two;_otext_file.close();_stack.push(1);";
                break;
            case Commands::Write:
                if (std::find(includes.begin(), includes.end(), "unistd.h") == includes.end())
                    includes.push_back("unistd.h");

                source += "_string_temp_one=_string_stack.top();_string_stack.pop();_temp_one=_stack.top();_stack.pop();_stack.push(write(_temp_one,_string_temp_one.c_str(),_string_temp_one.length()));";
                break;
            case Commands::Shell:
                if (std::find(includes.begin(), includes.end(), "stdlib.h") == includes.end())
                    includes.push_back("stdlib.h");

                source += "_string_temp_one=_string_stack.top();_string_stack.pop();_stack.push(system(_string_temp_one.c_str()));";
                break;
            case Commands::Quote:
                quoteRuns = true;
                break;
            case Commands::Emp:
                source += ("if(_stack.empty()){_stack.push(1);}else{_stack.push(0);};");
                break;
            case Commands::Emps:
                source += ("if(_string_stack.empty()){_stack.push(1);}else{_stack.push(0);};");
                break;
            case Commands::Size:
                source += ("_stack.push(_stack.size());");
                break;
            case Commands::Sizes:
                source += ("_stack.push(_string_stack.size());");
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
                else if (tokens[index - 1].key == Commands::Label)
                {
                    source += (token.value + ":");
                    break;
                }
                else if (tokens[index - 1].key == Commands::Jump)
                {
                    source += ("goto " + token.value + ";");
                    break;
                }

                switch (tokens[index - 1].key)
                {
                case Commands::Set:
                    source += (token.value + "=_stack.top();_stack.pop();");
                    break;
                case Commands::Let:
                    source += ("int " + token.value + "=0;");
                    break;
                case Commands::LetU:
                    source += ("unsigned int " + token.value + "=0;");
                    break;
                case Commands::LetM:
                    source += ("intmax_t " + token.value + "=0;");
                    break;
                case Commands::LetUM:
                    source += ("uintmax_t " + token.value + "=0;");
                    break;
                case Commands::Let64:
                    source += ("int64_t " + token.value + "=0;");
                    break;
                case Commands::LetU64:
                    source += ("uint64_t " + token.value + "=0;");
                    break;
                case Commands::Let32:
                    source += ("int23_t " + token.value + "=0;");
                    break;
                case Commands::LetU32:
                    source += ("uint23_t " + token.value + "=0;");
                    break;
                case Commands::Let16:
                    source += ("int16_t " + token.value + "=0;");
                    break;
                case Commands::LetU16:
                    source += ("uint16_t " + token.value + "=0;");
                    break;
                case Commands::Let8:
                    source += ("int8_t " + token.value + "=0;");
                    break;
                case Commands::LetU8:
                    source += ("uint16_t " + token.value + "=0;");
                    break;
                case Commands::Fetch:
                    source += ("_stack.push(" + token.value + ");");
                    break;
                case Commands::Sets:
                    source += (token.value + "=_string_stack.top();_string_stack.pop();");
                    break;
                case Commands::Lets:
                    source += ("std::string " + token.value + "=std::string();");
                    break;
                case Commands::Fetchs:
                    source += ("_string_stack.push(" + token.value + ");");
                    break;
                default:
                    std::cerr << "[L" << token.line << "]: Unknown token error\n";
                    exit(1);

                    break;
                }
                break;
            case Commands::String:
                if (tokens[index - 1].key == Commands::Import)
                {
                    std::string fileContent = std::string();
                    std::ifstream importFile(token.value);

                    if (!importFile)
                    {
                        std::cerr << "[L" << token.line << "]: Not a valid file path\n";
                        exit(1);
                    }

                    importFile.seekg(0, std::ios::end);
                    fileContent.reserve(importFile.tellg());
                    importFile.seekg(0, std::ios::beg);

                    fileContent.assign((std::istreambuf_iterator<char>(importFile)), std::istreambuf_iterator<char>());
                    importFile.close();

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
                }
                else if (tokens[index - 1].key == Commands::CImport)
                {
                    if (std::find(includes.begin(), includes.end(), token.value) == includes.end())
                        includes.push_back(token.value);
                    break;
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
        else if (quoteRuns && !syscallRuns)
        {
            if (token.key == Commands::Quote)
            {
                quoteRuns = false;
                continue;
            }

            source += ("_stack.push(" + std::to_string(token.key) + ");_string_stack.push(\"" + token.value + "\");");
        }
        else
        {
            switch (token.key)
            {
            case Commands::Syscall:
                if (syscallArgs.empty())
                {
                    std::cerr << "[L" << token.line << "]: Empty syscall\n";
                    exit(1);
                }
                if (std::find(includes.begin(), includes.end(), "unistd.h") == includes.end())
                    includes.push_back("unistd.h");

                if (std::find(includes.begin(), includes.end(), "sys/syscall.h") == includes.end())
                    includes.push_back("sys/syscall.h");

                syscallArgs.pop_back();
                syscallRuns = false;
                source += ("syscall(" + syscallArgs + ");");
                syscallArgs = std::string();
                break;
            case Commands::Number:
                syscallArgs += (token.value + ",");
                break;
            case Commands::String:
                syscallArgs += ("\"" + token.value + "\",");
                break;
            case Commands::Unknown:
                if (tokens[index - 1].key == Commands::Fetch)
                    syscallArgs += (token.value + ",");
                else if (tokens[index - 1].key == Commands::Fetchs)
                    syscallArgs += (token.value + ".c_str(),");
                else
                {
                    std::cerr << "[L" << token.line << "]: Unknown value\n";
                    exit(1);
                }
                break;
            default:
                if (!tokens[index - 1].key == Commands::Fetch || !tokens[index - 1].key == Commands::Fetchs)
                {
                    std::cerr << "[L" << token.line << "]: Not a valid syscall parameter\n";
                    exit(1);
                }

                break;
            }
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