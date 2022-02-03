#include <fstream>
#include <streambuf>

#include "./transpiler.cpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "File must be given";
        return 1;
    }

    std::string fileName = argv[1];
    std::string fileContent;

    std::ifstream textFile(fileName+".vi");

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
    lexer.collectedToken = std::string();
    lexer.tokens = std::vector<Token>();

    lexer.run();

    Transpiler transpiler;
    transpiler.tokens = lexer.tokens;

    transpiler.run();

    std::ofstream sourceOutput(fileName+".cpp");
    sourceOutput << transpiler.source << std::endl;
    sourceOutput.close();
}