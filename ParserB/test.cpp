#include <iostream>
#include <antlr4-runtime.h>
#include <BLexer.h>
int main(int argc, char const *argv[])
{
    std::ifstream ifs("mm.pdf");
    antlr4::ANTLRFileStream file;
    file.load(ifs);
    BLexer lexer(&file);
    antlr4::CommonTokenStream cts(&lexer);
    std::cout << 
    antlrcpp::toHexString(0b1010);
    return 0;
}
