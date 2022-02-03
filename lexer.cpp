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
    Halt,
    Unknown,
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
}

bool isNumber(std::string str)
{
    for (int index = 0; index < str.length(); index++)
    {
        if (std::isdigit(str[index]) == 0)
            return false;
    }

    return true;
}

void Lexer::determine()
{
    if (collectedToken.length() == 0)
        return;

    if (collectedToken == "halt")
        tokens.push_back(Token{line, Commands::Halt, std::string()});
    else
    {
        if (isNumber(collectedToken))
            tokens.push_back(Token{line, Commands::Number, collectedToken});
        else
            tokens.push_back(Token{line, Commands::Unknown, collectedToken});
    }

    collectedToken = std::string();
}