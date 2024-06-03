#include <iostream>
#include <BLexer.h>
#include <BParser.h>
class B : public BLexer
{
private:
public:
    using BLexer::BLexer;
    antlr4::Token *emitEOF() override
    {
        // 如果%%EOF未被匹配，则不能输出EOF，应该被忽略
        // 否则才能输出EOF
        if(this->getInputStream()->LA(1) == EOF)
            this->getInputStream()->consume();
        else
            std::cerr << "Not EOF" << std::endl;
        return BLexer::emitEOF();
    }
};
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
                file.load(ifs, true);
            }
            catch (antlr4::IllegalArgumentException e)
            {
                std::cerr << e.what() << std::endl;
                ifs.close();
                continue;
            }
            B lexer(&file);
            antlr4::CommonTokenStream cts(&lexer);
            BParser parser(&cts);
            parser.start();

            ifs.close();
        }
    }

    return 0;
}
