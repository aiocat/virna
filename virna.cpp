#include <fstream>
#include <streambuf>

#include "./lexer.cpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "File must be given";
        return 1;
    }

    std::string fileName = argv[1];
    std::string fileContent;

    std::ifstream textFile(fileName);

    if (!textFile)
    {
        std::cerr << "Not a valid file path";
        return 1;
    }

    textFile.seekg(0, std::ios::end);
    fileContent.reserve(textFile.tellg());
    textFile.seekg(0, std::ios::beg);

    fileContent.assign((std::istreambuf_iterator<char>(textFile)), std::istreambuf_iterator<char>());

    Lexer lexer;
    lexer.line = 1;
    lexer.raw = fileContent;
    lexer.collectedToken = std::string();
    lexer.tokens = std::vector<Token>();

    lexer.run();

    for (auto iterate = lexer.tokens.begin(); iterate != lexer.tokens.end(); ++iterate)
    {
        std::cout << iterate->key << " " << iterate->value << "\n";
    }
}