#include <fstream>
#include <antlr4-runtime.h>
#include <mathLexer.h>
#include <mathParser.h>
int main(int argc, char const *argv[])
{
    std::ofstream log("log.txt");
    auto sb = std::cout.rdbuf(log.rdbuf());
    for (size_t i = 1; argv[i]; ++i)
    {
        std::cout << "-----" << argv[i] << "-----\n";
        std::ifstream ifs(argv[i], std::ios_base::binary);
        antlr4::ANTLRFileStream input;
        input.load(ifs);
        mathLexer lexer(&input);
        antlr4::CommonTokenStream ct(&lexer);
        mathParser parser(&ct);
        parser.start();
        // parser.array();
        // parser.stream();
        // antlr4::Token *t;
        // t->

        ifs.close();
    }
    std::cout.rdbuf(sb);
    log.close();
    return 0;
}
