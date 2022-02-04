#include <iostream>
#include <vector>
#include <string>

enum Commands
{
    Number,
    String,
    Adds,
    Add,
    Sub,
    Dimo,
    Mul,
    Ret,
    Unknown,
    In,
    End,
    Set,
    Let,
    Sets,
    Lets,
    Put,
    Putc,
    Puts,
    Compare,
    If,
    Else,
    While,
    Break,
    Skip,
    Dup,
    Dups,
    Swap,
    Swaps,
    Pop,
    Pops,
    Eqs,
    Lens,
    Trns,
    Revs,
    Get,
    Gets,
    Import,
    Inline,
    Readf,
    Writef,
    Appendc,
    Write,
    Shell
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
    int line;
    bool collectingString;
    bool inComment;
    std::string raw;
    std::string collectedToken;
    std::vector<Token> tokens;

    void run();
    void determine();
};

void Lexer::run()
{
    collectingString = false;
    inComment = false;

    for (int index = 0; index < raw.length(); index++)
    {
        char character = raw[index];

        if (!collectingString && !inComment)
        {
            switch (character)
            {
            case '\r':
                break;
            case '\n':
                determine();
                line++;
                break;
            case '-':
                tokens.push_back(Token{
                    line, Commands::Sub, std::string()});
                break;
            case '*':
                tokens.push_back(Token{
                    line, Commands::Mul, std::string()});
                break;
            case ' ':
                determine();
                break;
            case '#':
                inComment = true;
                break;
            case '"':
                collectingString = true;
                break;
            default:
                collectedToken += character;
                break;
            }

            if (index + 1 == raw.length())
                determine();
        } else if (collectingString) {
            if (character == '"' && raw[index - 1] != '\\') {
                tokens.push_back(Token{line, Commands::String, collectedToken});
                collectedToken = "";
                collectingString = false;
            } else {
                collectedToken += character;
            }
        } else {
            if (character == '#') {
                inComment = false;
            }
        }
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
    else if (collectedToken == "sets")
        tokens.push_back(Token{line, Commands::Sets, std::string()});
    else if (collectedToken == "lets")
        tokens.push_back(Token{line, Commands::Lets, std::string()});
    else if (collectedToken == "put")
        tokens.push_back(Token{line, Commands::Put, std::string()});
    else if (collectedToken == "puts")
        tokens.push_back(Token{line, Commands::Puts, std::string()});
    else if (collectedToken == "if")
        tokens.push_back(Token{line, Commands::If, std::string()});
    else if (collectedToken == "else")
        tokens.push_back(Token{line, Commands::Else, std::string()});
    else if (collectedToken == "while")
        tokens.push_back(Token{line, Commands::While, std::string()});
    else if (collectedToken == "break")
        tokens.push_back(Token{line, Commands::Break, std::string()});
    else if (collectedToken == "skip")
        tokens.push_back(Token{line, Commands::Skip, std::string()});
    else if (collectedToken == "dup")
        tokens.push_back(Token{line, Commands::Dup, std::string()});
    else if (collectedToken == "dups")
        tokens.push_back(Token{line, Commands::Dups, std::string()});
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
    else if (collectedToken == "dimo")
        tokens.push_back(Token{line, Commands::Dimo, std::string()});
    else if (collectedToken == "swap")
        tokens.push_back(Token{line, Commands::Swap, std::string()});
    else if (collectedToken == "pop")
        tokens.push_back(Token{line, Commands::Pop, std::string()});
    else if (collectedToken == "swaps")
        tokens.push_back(Token{line, Commands::Swaps, std::string()});
    else if (collectedToken == "pops")
        tokens.push_back(Token{line, Commands::Pops, std::string()});
    else if (collectedToken == "eqs")
        tokens.push_back(Token{line, Commands::Eqs, std::string()});
    else if (collectedToken == "putc")
        tokens.push_back(Token{line, Commands::Putc, std::string()});
    else if (collectedToken == "lens")
        tokens.push_back(Token{line, Commands::Lens, std::string()});
    else if (collectedToken == "trns")
        tokens.push_back(Token{line, Commands::Trns, std::string()});
    else if (collectedToken == "revs")
        tokens.push_back(Token{line, Commands::Revs, std::string()});
    else if (collectedToken == "get")
        tokens.push_back(Token{line, Commands::Get, std::string()});
    else if (collectedToken == "gets")
        tokens.push_back(Token{line, Commands::Gets, std::string()});
    else if (collectedToken == "import")
        tokens.push_back(Token{line, Commands::Import, std::string()});
    else if (collectedToken == "inline")
        tokens.push_back(Token{line, Commands::Inline, std::string()});
    else if (collectedToken == "readf")
        tokens.push_back(Token{line, Commands::Readf, std::string()});
    else if (collectedToken == "writef")
        tokens.push_back(Token{line, Commands::Writef, std::string()});
    else if (collectedToken == "write")
        tokens.push_back(Token{line, Commands::Write, std::string()});
    else if (collectedToken == "appendc")
        tokens.push_back(Token{line, Commands::Appendc, std::string()});
    else if (collectedToken == "shell")
        tokens.push_back(Token{line, Commands::Shell, std::string()});
    else if (collectedToken == "+")
        tokens.push_back(Token{line, Commands::Add, std::string()});
    else if (collectedToken == "++")
        tokens.push_back(Token{line, Commands::Adds, std::string()});
    else
    {
        if (isNumber(collectedToken))
            tokens.push_back(Token{line, Commands::Number, collectedToken});
        else if (collectedToken.length() == 2 && collectedToken[0] == '\'')
            tokens.push_back(Token{line, Commands::Number, std::to_string((int)collectedToken[1])});
        else
            tokens.push_back(Token{line, Commands::Unknown, collectedToken});
    }

    collectedToken = std::string();
};