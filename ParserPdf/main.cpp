#include <fstream>
#include <antlr4-runtime.h>
#include <pdLexer.h>
#include <pdfParser.h>
#include <format.h>
#include <pdListener.h>
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
        antlr4::CommonTokenStream ct(&lexer);
        // while (ct.LA(1) != antlr4::Token::EOF)
        // {
        //     ofs << ct.LT(1)->getText() << '\n';
        //     ct.consume();
        // }
        pdfParser parser(&ct);
        pdListener listener;
        parser.addParseListener(&listener);
        auto &&node = parser.pdf();
        // ofs << node->getText();
        // parser.array();
        // parser.stream();
        // antlr4::Token *t;
        bool split = false;
        antlr4::pdfFormatVisitor ft(ofs,split);
        ft.visit(node);
        ofs.close();
        ifs.close();
        // break;
    }
    return 0;
}
