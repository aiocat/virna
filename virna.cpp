#include <fstream>
#include <streambuf>
#include <unistd.h>

#include "./transpiler.cpp"

std::string getDir(std::string str);
std::string getFileName(std::string str);
std::string getBaseName(std::string str);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "File must be given";
        return 1;
    }

    std::string fileName = argv[1];
    std::string fileContent = std::string();

    std::ifstream textFile(fileName + ".vi");

    if (!textFile)
    {
        std::cerr << "Not a valid file path";
        return 1;
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
    transpiler.allowInclude = true;

    chdir(getDir(fileName).c_str());
    transpiler.run();

    std::ofstream sourceOutput(getBaseName(fileName) + ".cpp");
    sourceOutput << transpiler.source << std::endl;
    sourceOutput.close();
}

std::string getDir(std::string str)
{
    size_t found;
    found = str.find_last_of("/\\");
    return str.substr(0, found);
}

std::string getFileName(std::string str)
{
    size_t found;
    found = str.find_last_of(".");
    return str.substr(0, found);
}

std::string getBaseName(std::string str)
{
    return str.substr(str.find_last_of("/\\") + 1);
}