#pragma once
#include <antlr4-runtime.h>
class pdLexerErrorListener : public antlr4::BaseErrorListener
{
private:
public:
    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
                             const std::string &msg, std::exception_ptr e) override;
};