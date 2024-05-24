#include <iostream>
#include <BLexer.h>
#include <BParser.h>
int main(int argc, char const *argv[])
{
    for (size_t i = 1; argv[i]; ++i)
    {
        std::ifstream ifs(argv[i]);
        if (ifs)
        {
            antlr4::ANTLRFileStream file;
            try
            {
                file.load(ifs);
            }
            catch (antlr4::IllegalArgumentException e)
            {
            }
            BLexer lexer(&file);
            antlr4::CommonTokenStream cts(&lexer);

            std::cout << lexer.getSourceName();

            ifs.close();
        }
    }

    return 0;
}
