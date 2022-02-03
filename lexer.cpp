#include <iostream>
#include <vector>
#include <string>

enum Commands
{
    Number,
    Add,
    Sub,
    Div,
    Mul,
    Ret,
    Unknown,
    In,
    End,
    Set,
    Let,
    Dump,
    Compare,
    If,
    Else
};

struct Token
{
    int line;
    Commands key;
    std::string value;
};

class Lexer
{
public:
    std::string raw;
    std::string collectedToken;
    int line;
    std::vector<Token> tokens;

    void run();
    void determine();
};

void Lexer::run()
{
    for (int index = 0; index < raw.length(); index++)
    {
        char character = raw[index];

        switch (character)
        {
        case '\r':
            break;
        case '\n':
            determine();
            line++;
            break;
        case '+':
            tokens.push_back(Token{
                line, Commands::Add, std::string()});
            break;
        case '-':
            tokens.push_back(Token{
                line, Commands::Sub, std::string()});
            break;
        case '/':
            tokens.push_back(Token{
                line, Commands::Div, std::string()});
            break;
        case '*':
            tokens.push_back(Token{
                line, Commands::Mul, std::string()});
            break;
        case ' ':
            determine();
            break;
        default:
            collectedToken += character;
            break;
        }

        if (index + 1 == raw.length())
            determine();
    }
};

bool isNumber(std::string str)
{
    for (int index = 0; index < str.length(); index++)
    {
        if (std::isdigit(str[index]) == 0)
            return false;
    }

    return true;
};

void Lexer::determine()
{
    if (collectedToken.length() == 0)
        return;

    if (collectedToken == "ret")
        tokens.push_back(Token{line, Commands::Ret, std::string()});
    else if (collectedToken == "in")
        tokens.push_back(Token{line, Commands::In, std::string()});
    else if (collectedToken == "end")
        tokens.push_back(Token{line, Commands::End, std::string()});
    else if (collectedToken == "set")
        tokens.push_back(Token{line, Commands::Set, std::string()});
    else if (collectedToken == "let")
        tokens.push_back(Token{line, Commands::Let, std::string()});
    else if (collectedToken == "dump")
        tokens.push_back(Token{line, Commands::Dump, std::string()});
    else if (collectedToken == "if")
        tokens.push_back(Token{line, Commands::If, std::string()});
    else if (collectedToken == "else")
        tokens.push_back(Token{line, Commands::Else, std::string()});
    else if (collectedToken == "=")
        tokens.push_back(Token{line, Commands::Compare, "=="});
    else if (collectedToken == "!")
        tokens.push_back(Token{line, Commands::Compare, "!="});
    else if (collectedToken == ">")
        tokens.push_back(Token{line, Commands::Compare, ">"});
    else if (collectedToken == "<")
        tokens.push_back(Token{line, Commands::Compare, "<"});
    else if (collectedToken == ">=")
        tokens.push_back(Token{line, Commands::Compare, ">="});
    else if (collectedToken == "<=")
        tokens.push_back(Token{line, Commands::Compare, "<="});
    else
    {
        if (isNumber(collectedToken))
            tokens.push_back(Token{line, Commands::Number, collectedToken});
        else
            tokens.push_back(Token{line, Commands::Unknown, collectedToken});
    }

    collectedToken = std::string();
};