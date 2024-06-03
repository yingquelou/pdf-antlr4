#include <fstream>
#include <antlr4-runtime.h>
#include <pdLexer.h>
#include <pdfParser.h>
// #include "format.h"
#include "pdListener.h"
#include "pdLexerErrorListener.h"
int main(int argc, char const *argv[])
{
    for (size_t i = 1; argv[i]; ++i)
    {
        std::cout << "-----" << argv[i] << "-----\n";
        std::string s(argv[i]);
        s += ".txt";
        std::ofstream ofs(s);
        std::ifstream ifs(argv[i], std::ios_base::binary);
        antlr4::ANTLRFileStream input;
        input.load(ifs, true);
        pdLexer lexer(&input);
        pdLexerErrorListener errorListener;
        lexer.removeErrorListeners();
        lexer.addErrorListener(&errorListener);
        antlr4::CommonTokenStream ct(&lexer);
        pdfParser parser(&ct);
        pdListener listener;
        parser.addParseListener(&listener);
        parser.start();
        // auto &&node = parser.start();
        // ofs << node->getText();
        // parser.array();
        // parser.stream();
        // antlr4::Token *t;
        // antlr4::format ft(ofs);
        // ft.visit(node);
        ofs.close();
        ifs.close();
    }
    return 0;
}
