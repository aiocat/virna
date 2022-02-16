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
    Shell,
    Mod,
    Neg,
    RightShift,
    LeftShift,
    BitwiseOr,
    BitwiseAnd,
    BitwiseNot,
    BitwiseXor,
    Repeat,
    Fetch,
    Fetchs,
    Quote,
    Try,
    Catch,
    Err,
    Getch,
    Forever,
    Rand,
    Sleep,
    Emp,
    Emps,
    Size,
    Sizes,
    Syscall,
    Label,
    Jump,
    CCode,
    CImport,
    Defer,
    LetU,
    Let64,
    LetU64,
    Let32,
    LetU32,
    Let16,
    LetU16,
    Let8,
    LetU8,
    LetM,
    LetUM,
    Iters
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
    bool collectingChar;
    bool inComment;
    bool collectingC;
    std::string raw;
    std::string collectedToken;
    std::vector<Token> tokens;

    void run();
    void determine();
};

void Lexer::run()
{
    collectingString, inComment, collectingChar, collectingC = false, false, false, false;

    for (int index = 0; index < raw.length(); index++)
    {
        char character = raw[index];

        if (!collectingString && !inComment && !collectingChar && !collectingC)
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
            case '|':
                tokens.push_back(Token{
                    line, Commands::BitwiseOr, std::string()});
                break;
            case '&':
                tokens.push_back(Token{
                    line, Commands::BitwiseAnd, std::string()});
                break;
            case '~':
                tokens.push_back(Token{
                    line, Commands::BitwiseNot, std::string()});
                break;
            case '^':
                tokens.push_back(Token{
                    line, Commands::BitwiseXor, std::string()});
                break;
            case '%':
                tokens.push_back(Token{
                    line, Commands::Mod, std::string()});
                break;
            case ' ':
                determine();
                break;
            case '#':
                inComment = true;
                break;
            case '\'':
                collectingChar = true;
                break;
            case '"':
                collectingString = true;
                break;
            case '`':
                collectingC = true;
                break;
            default:
                collectedToken += character;
                break;
            }

            if (index + 1 == raw.length())
                determine();
        }
        else if (collectingString && !collectingChar && !collectingC)
        {
            if (character == '"' && raw[index - 1] != '\\')
            {
                tokens.push_back(Token{line, Commands::String, collectedToken});
                collectedToken = "";
                collectingString = false;
            }
            else
            {
                collectedToken += character;
            }
        }
        else if (inComment && !collectingChar && !collectingC)
        {
            if (character == '#')
            {
                inComment = false;
            }
        }
        else if (collectingChar && !collectingC)
        {
            if (character == '\'' && raw[index - 1] != '\\')
            {
                char collectedChar = '\0';

                if (collectedToken == "\\n")
                    collectedChar = '\n';
                else if (collectedToken == "\\r")
                    collectedChar = '\r';
                else if (collectedToken == "\\t")
                    collectedChar = '\t';
                else if (collectedToken == "\\'")
                    collectedChar = '\'';
                else if (collectedToken.length() != 1)
                {
                    std::cerr << "[L" << line << "]: Incorrect character usage\n";
                    exit(1);
                }
                else
                    collectedChar = collectedToken[0];

                tokens.push_back(Token{line, Commands::Number, std::to_string((int)collectedChar)});
                collectingChar = false;
                collectedToken = "";
            }
            else
                collectedToken += character;
        }
        else
        {
            if (character == '`' && raw[index - 1] != '\\')
            {
                tokens.push_back(Token{line, Commands::CCode, collectedToken});
                collectedToken = "";
                collectingC = false;
            }
            else if (character == '`' && raw[index - 1] == '\\')
            {
                collectedToken.pop_back();
                collectedToken += "`";
            }
            else
                collectedToken += character;
        }
    }
};

bool isHexN(std::string str)
{
    if (!(str[0] == '0' && str[1] == 'x'))
        return false;
    if (str.length() < 3)
        return false;

    for (int index = 2; index < str.length(); index++)
    {
        if (std::isdigit(str[index]) != 0 || (str[index] == 'A' || str[index] == 'B' || str[index] == 'C' || str[index] == 'D' || str[index] == 'E' || str[index] == 'F' ||
                                              str[index] == 'a' || str[index] == 'b' || str[index] == 'c' || str[index] == 'd' || str[index] == 'e' || str[index] == 'f'))
            continue;
        else
            return false;
    }

    return true;
}

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
    else if (collectedToken == "letu")
        tokens.push_back(Token{line, Commands::LetU, std::string()});
    else if (collectedToken == "letm")
        tokens.push_back(Token{line, Commands::LetM, std::string()});
    else if (collectedToken == "letum")
        tokens.push_back(Token{line, Commands::LetUM, std::string()});
    else if (collectedToken == "let64")
        tokens.push_back(Token{line, Commands::Let64, std::string()});
    else if (collectedToken == "letu64")
        tokens.push_back(Token{line, Commands::LetU64, std::string()});
    else if (collectedToken == "let32")
        tokens.push_back(Token{line, Commands::Let32, std::string()});
    else if (collectedToken == "letu32")
        tokens.push_back(Token{line, Commands::LetU32, std::string()});
    else if (collectedToken == "let16")
        tokens.push_back(Token{line, Commands::Let16, std::string()});
    else if (collectedToken == "letu16")
        tokens.push_back(Token{line, Commands::LetU16, std::string()});
    else if (collectedToken == "let8")
        tokens.push_back(Token{line, Commands::Let8, std::string()});
    else if (collectedToken == "letu8")
        tokens.push_back(Token{line, Commands::LetU8, std::string()});
    else if (collectedToken == "sets")
        tokens.push_back(Token{line, Commands::Sets, std::string()});
    else if (collectedToken == "lets")
        tokens.push_back(Token{line, Commands::Lets, std::string()});
    else if (collectedToken == "put")
        tokens.push_back(Token{line, Commands::Put, std::string()});
    else if (collectedToken == "puts")
        tokens.push_back(Token{line, Commands::Puts, std::string()});
    else if (collectedToken == "forever")
        tokens.push_back(Token{line, Commands::Forever, std::string()});
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
    else if (collectedToken == "neg")
        tokens.push_back(Token{line, Commands::Neg, std::string()});
    else if (collectedToken == "fetch")
        tokens.push_back(Token{line, Commands::Fetch, std::string()});
    else if (collectedToken == "fetchs")
        tokens.push_back(Token{line, Commands::Fetchs, std::string()});
    else if (collectedToken == "quote")
        tokens.push_back(Token{line, Commands::Quote, std::string()});
    else if (collectedToken == "sleep")
        tokens.push_back(Token{line, Commands::Sleep, std::string()});
    else if (collectedToken == "iters")
        tokens.push_back(Token{line, Commands::Iters, std::string()});
    else if (collectedToken == "try")
        tokens.push_back(Token{line, Commands::Try, std::string()});
    else if (collectedToken == "catch")
        tokens.push_back(Token{line, Commands::Catch, std::string()});
    else if (collectedToken == "err")
        tokens.push_back(Token{line, Commands::Err, std::string()});
    else if (collectedToken == "getch")
        tokens.push_back(Token{line, Commands::Getch, std::string()});
    else if (collectedToken == "emp")
        tokens.push_back(Token{line, Commands::Emp, std::string()});
    else if (collectedToken == "emps")
        tokens.push_back(Token{line, Commands::Emps, std::string()});
    else if (collectedToken == "size")
        tokens.push_back(Token{line, Commands::Size, std::string()});
    else if (collectedToken == "sizes")
        tokens.push_back(Token{line, Commands::Sizes, std::string()});
    else if (collectedToken == "=")
        tokens.push_back(Token{line, Commands::Compare, "=="});
    else if (collectedToken == "!")
        tokens.push_back(Token{line, Commands::Compare, "!="});
    else if (collectedToken == ">")
        tokens.push_back(Token{line, Commands::Compare, ">"});
    else if (collectedToken == "<")
        tokens.push_back(Token{line, Commands::Compare, "<"});
    else if (collectedToken == ">>")
        tokens.push_back(Token{line, Commands::RightShift, ">"});
    else if (collectedToken == "<<")
        tokens.push_back(Token{line, Commands::LeftShift, "<"});
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
    else if (collectedToken == "cimport")
        tokens.push_back(Token{line, Commands::CImport, std::string()});
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
    else if (collectedToken == "repeat")
        tokens.push_back(Token{line, Commands::Repeat, std::string()});
    else if (collectedToken == "rand")
        tokens.push_back(Token{line, Commands::Rand, std::string()});
    else if (collectedToken == "syscall")
        tokens.push_back(Token{line, Commands::Syscall, std::string()});
    else if (collectedToken == "label")
        tokens.push_back(Token{line, Commands::Label, std::string()});
    else if (collectedToken == "jump")
        tokens.push_back(Token{line, Commands::Jump, std::string()});
    else if (collectedToken == "defer")
        tokens.push_back(Token{line, Commands::Defer, std::string()});
    else if (collectedToken == "+")
        tokens.push_back(Token{line, Commands::Add, std::string()});
    else if (collectedToken == "++")
        tokens.push_back(Token{line, Commands::Adds, std::string()});
    else
    {
        if (isNumber(collectedToken) || isHexN(collectedToken))
            tokens.push_back(Token{line, Commands::Number, collectedToken});
        else
            tokens.push_back(Token{line, Commands::Unknown, collectedToken});
    }

    collectedToken = std::string();
};